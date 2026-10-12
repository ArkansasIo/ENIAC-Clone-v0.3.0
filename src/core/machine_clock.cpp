#include "eniac/core/machine_clock.hpp"
namespace eniac {
void MachineClock::tick() noexcept { ++cycles_; }
void MachineClock::reset() noexcept { cycles_ = 0; }
std::uint64_t MachineClock::cycles() const noexcept { return cycles_; }
} // namespace eniac
