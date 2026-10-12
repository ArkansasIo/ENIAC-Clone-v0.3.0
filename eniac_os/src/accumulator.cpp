#include "eniac_os/accumulator.hpp"
#include <limits>
#include <sstream>
#include <stdexcept>

namespace eniac_os {
namespace {
void require_index(std::size_t index) {
    if (index >= accumulator_count) throw std::out_of_range("accumulator index must be 0..19");
}
std::int64_t checked_add(std::int64_t a, std::int64_t b) {
    constexpr auto lo = std::numeric_limits<std::int64_t>::min();
    constexpr auto hi = std::numeric_limits<std::int64_t>::max();
    if ((b > 0 && a > hi - b) || (b < 0 && a < lo - b))
        throw std::overflow_error("decimal accumulator overflow");
    return a + b;
}
std::int64_t checked_mul(std::int64_t a, std::int64_t b) {
    if (a == 0 || b == 0) return 0;
    constexpr auto lo = std::numeric_limits<std::int64_t>::min();
    constexpr auto hi = std::numeric_limits<std::int64_t>::max();
    if ((a == -1 && b == lo) || (b == -1 && a == lo))
        throw std::overflow_error("decimal accumulator overflow");
    if (a > 0) {
        if ((b > 0 && a > hi / b) || (b < 0 && b < lo / a))
            throw std::overflow_error("decimal accumulator overflow");
    } else {
        if ((b > 0 && a < lo / b) || (b < 0 && a < hi / b))
            throw std::overflow_error("decimal accumulator overflow");
    }
    return a * b;
}
}
void AccumulatorBank::reset() noexcept { values_.fill(0); }
bool AccumulatorBank::valid_index(std::size_t index) const noexcept { return index < accumulator_count; }
std::int64_t AccumulatorBank::get(std::size_t index) const { require_index(index); return values_[index]; }
void AccumulatorBank::set(std::size_t index, std::int64_t value) { require_index(index); values_[index] = value; }
void AccumulatorBank::add(std::size_t index, std::int64_t value) { set(index, checked_add(get(index), value)); }
void AccumulatorBank::subtract(std::size_t index, std::int64_t value) {
    if (value == std::numeric_limits<std::int64_t>::min()) {
        const auto current = get(index);
        if (current >= 0) throw std::overflow_error("decimal accumulator overflow");
        set(index, current - value);
        return;
    }
    add(index, -value);
}
void AccumulatorBank::multiply(std::size_t index, std::int64_t value) { set(index, checked_mul(get(index), value)); }
void AccumulatorBank::divide(std::size_t index, std::int64_t value) {
    if (value == 0) throw std::domain_error("division by zero");
    if (get(index) == std::numeric_limits<std::int64_t>::min() && value == -1)
        throw std::overflow_error("decimal accumulator overflow");
    set(index, get(index) / value);
}
std::string AccumulatorBank::describe() const {
    std::ostringstream out;
    for (std::size_t i = 0; i < values_.size(); ++i) {
        out << 'A' << i << '=' << values_[i];
        if (i + 1 != values_.size()) out << "  ";
        if ((i + 1) % 5 == 0) out << '\n';
    }
    return out.str();
}
} // namespace eniac_os
