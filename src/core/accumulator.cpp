#include "eniac/core/accumulator.hpp"

namespace eniac {
Accumulator::Accumulator(long long value) { set(value); }
long long Accumulator::value() const noexcept { return value_; }
const AccumulatorFlags& Accumulator::flags() const noexcept { return flags_; }
void Accumulator::set(long long value) noexcept {
    value_ = value;
    flags_.negative = value < 0;
    flags_.overflow = false;
}
void Accumulator::set_flags(AccumulatorFlags flags) noexcept { flags_ = flags; }
void Accumulator::clear() noexcept { value_ = 0; flags_ = {}; }
} // namespace eniac
