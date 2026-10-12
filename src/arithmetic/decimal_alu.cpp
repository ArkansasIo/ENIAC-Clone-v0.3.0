#include "eniac/arithmetic/decimal_alu.hpp"
#include <limits>
namespace eniac {
namespace {
constexpr long long limit = 9999999999LL;
ArithmeticResult normalize(__int128 value) {
    const bool overflow = value > limit || value < -limit;
    const __int128 modulus = static_cast<__int128>(limit) * 2 + 1;
    value = (value + limit) % modulus;
    if (value < 0) value += modulus;
    value -= limit;
    return {static_cast<long long>(value), overflow};
}
}
ArithmeticResult DecimalALU::add(long long left, long long right) const { return normalize(static_cast<__int128>(left) + right); }
ArithmeticResult DecimalALU::subtract(long long left, long long right) const { return normalize(static_cast<__int128>(left) - right); }
ArithmeticResult DecimalALU::multiply(long long left, long long right) const { return normalize(static_cast<__int128>(left) * right); }
} // namespace eniac
