#include "eniac/arithmetic/decimal_alu.hpp"

#include <cstdint>

namespace eniac {
namespace {

constexpr long long limit = 9999999999LL;

// Signed 128-bit wide integer represented as two 64-bit limbs (hi:lo),
// in two's-complement little-endian order. This is portable across MSVC,
// GCC and Clang and deliberately avoids the non-standard `__int128` type.
struct wide {
    std::uint64_t lo{};
    std::uint64_t hi{};
};

constexpr wide from_signed(long long value) noexcept {
    const auto magnitude = static_cast<std::uint64_t>(value);
    const std::uint64_t sign = value < 0 ? ~std::uint64_t{0} : std::uint64_t{0};
    return {magnitude, sign};
}

constexpr bool is_negative(wide value) noexcept { return (value.hi & 0x8000000000000000ULL) != 0; }

constexpr bool less_than(wide a, wide b) noexcept {
    if (is_negative(a) != is_negative(b)) return is_negative(a);
    if (a.hi != b.hi) return a.hi < b.hi;
    return a.lo < b.lo;
}

constexpr wide negate(wide value) noexcept {
    const std::uint64_t lo = ~value.lo + 1ULL;
    const std::uint64_t carry = lo == 0 ? 1ULL : 0ULL;
    return {lo, ~value.hi + carry};
}

constexpr wide wide_add(wide a, wide b) noexcept {
    const std::uint64_t lo = a.lo + b.lo;
    const std::uint64_t carry = lo < a.lo ? 1ULL : 0ULL;
    return {lo, a.hi + b.hi + carry};
}

constexpr wide wide_subtract(wide a, wide b) noexcept { return wide_add(a, negate(b)); }

constexpr wide wide_multiply(wide a, wide b) noexcept {
    const std::uint64_t a0 = a.lo & 0xFFFFFFFFULL;
    const std::uint64_t a1 = a.lo >> 32;
    const std::uint64_t a2 = a.hi & 0xFFFFFFFFULL;
    const std::uint64_t a3 = a.hi >> 32;
    const std::uint64_t b0 = b.lo & 0xFFFFFFFFULL;
    const std::uint64_t b1 = b.lo >> 32;
    const std::uint64_t b2 = b.hi & 0xFFFFFFFFULL;
    const std::uint64_t b3 = b.hi >> 32;

    const std::uint64_t p00 = a0 * b0;
    const std::uint64_t p01 = a0 * b1;
    const std::uint64_t p02 = a0 * b2;
    const std::uint64_t p03 = a0 * b3;
    const std::uint64_t p10 = a1 * b0;
    const std::uint64_t p11 = a1 * b1;
    const std::uint64_t p12 = a1 * b2;
    const std::uint64_t p13 = a1 * b3;
    const std::uint64_t p20 = a2 * b0;
    const std::uint64_t p21 = a2 * b1;
    const std::uint64_t p22 = a2 * b2;
    const std::uint64_t p23 = a2 * b3;
    const std::uint64_t p30 = a3 * b0;
    const std::uint64_t p31 = a3 * b1;
    const std::uint64_t p32 = a3 * b2;
    const std::uint64_t p33 = a3 * b3;

    // Accumulate 32-bit partial products column by column, carrying upward.
    std::uint32_t result[4] = {0, 0, 0, 0};
    std::uint64_t carry = 0;

    carry += (p00 & 0xFFFFFFFFULL);
    result[0] = static_cast<std::uint32_t>(carry);
    carry >>= 32;
    carry += (p00 >> 32) + (p01 & 0xFFFFFFFFULL) + (p10 & 0xFFFFFFFFULL);
    result[1] = static_cast<std::uint32_t>(carry);
    carry >>= 32;
    carry += (p01 >> 32) + (p10 >> 32) + (p02 & 0xFFFFFFFFULL) + (p11 & 0xFFFFFFFFULL) + (p20 & 0xFFFFFFFFULL);
    result[2] = static_cast<std::uint32_t>(carry);
    carry >>= 32;
    carry += (p02 >> 32) + (p11 >> 32) + (p20 >> 32) +
             (p03 & 0xFFFFFFFFULL) + (p12 & 0xFFFFFFFFULL) + (p21 & 0xFFFFFFFFULL) + (p30 & 0xFFFFFFFFULL);
    result[3] = static_cast<std::uint32_t>(carry);

    const std::uint64_t lo = static_cast<std::uint64_t>(result[0]) | (static_cast<std::uint64_t>(result[1]) << 32);
    const std::uint64_t hi = static_cast<std::uint64_t>(result[2]) | (static_cast<std::uint64_t>(result[3]) << 32);
    return {lo, hi};
}

// Unsigned long division of a wide magnitude by a small positive modulus
// (modulus < 2^35). Folds the 128-bit magnitude in 32-bit chunks while
// keeping every intermediate product below 2^64.
std::uint64_t remainder_of(wide magnitude, std::uint64_t modulus) noexcept {
    std::uint64_t result = 0;
    const std::uint32_t chunks[4] = {
        static_cast<std::uint32_t>(magnitude.hi >> 32),
        static_cast<std::uint32_t>(magnitude.hi),
        static_cast<std::uint32_t>(magnitude.lo >> 32),
        static_cast<std::uint32_t>(magnitude.lo),
    };
    for (const std::uint32_t chunk : chunks) {
        // result < modulus < 2^35; split the x2^32 shift into two x2^16 steps
        // so each product stays below 2^51 before the modulo reduction.
        result = ((result * 0x10000ULL) % modulus * 0x10000ULL + chunk) % modulus;
    }
    return result;
}

// Reduce a wide value into [-limit, limit] and report overflow.
ArithmeticResult normalize(wide value) noexcept {
    const wide upper = from_signed(limit);
    const wide lower = from_signed(-limit);
    const bool overflow = less_than(upper, value) || less_than(value, lower);
    const auto modulus = static_cast<std::uint64_t>(2 * limit + 1);

    wide shifted = wide_add(value, from_signed(limit));
    const bool negative = is_negative(shifted);
    const wide magnitude = negative ? negate(shifted) : shifted;

    std::uint64_t remainder = remainder_of(magnitude, modulus);
    if (negative && remainder != 0) remainder = modulus - remainder;

    const long long normalized = static_cast<long long>(remainder) - limit;
    return {normalized, overflow};
}

} // namespace

ArithmeticResult DecimalALU::add(long long left, long long right) const {
    return normalize(wide_add(from_signed(left), from_signed(right)));
}

ArithmeticResult DecimalALU::subtract(long long left, long long right) const {
    return normalize(wide_subtract(from_signed(left), from_signed(right)));
}

ArithmeticResult DecimalALU::multiply(long long left, long long right) const {
    return normalize(wide_multiply(from_signed(left), from_signed(right)));
}

} // namespace eniac
