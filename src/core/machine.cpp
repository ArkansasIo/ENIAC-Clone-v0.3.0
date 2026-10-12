#include "eniac/core/machine.hpp"

#include "eniac/arithmetic/decimal_alu.hpp"

namespace eniac {
Machine::Machine(MachineConfig config) : config_(std::move(config)) {
    events_.record("Machine constructed: " + config_.name);
}
MachineState Machine::state() const noexcept { return state_; }
const MachineConfig& Machine::config() const noexcept { return config_; }
AccumulatorBank& Machine::accumulators() noexcept { return accumulators_; }
const AccumulatorBank& Machine::accumulators() const noexcept { return accumulators_; }
MachineClock& Machine::clock() noexcept { return clock_; }
const MachineClock& Machine::clock() const noexcept { return clock_; }
EventLog& Machine::events() noexcept { return events_; }
const EventLog& Machine::events() const noexcept { return events_; }

bool Machine::start() {
    if (state_ != MachineState::Stopped) return false;
    state_ = MachineState::Running;
    events_.record("Machine started");
    return true;
}
bool Machine::stop() {
    if (state_ != MachineState::Running && state_ != MachineState::Paused) return false;
    state_ = MachineState::Stopped;
    events_.record("Machine stopped");
    return true;
}
bool Machine::reset() {
    if (state_ == MachineState::Running) return false;
    accumulators_.clear();
    clock_.reset();
    state_ = MachineState::Stopped;
    events_.record("Machine reset");
    return true;
}
void Machine::tick() noexcept {
    if (state_ == MachineState::Running) clock_.tick();
}
bool Machine::load_value(std::size_t index, long long value) noexcept {
    if (state_ != MachineState::Running) return false;
    auto* accumulator = accumulators_.at(index);
    if (!accumulator) return false;
    accumulator->set(value);
    return true;
}
bool Machine::add(int destination, int source) noexcept {
    if (state_ != MachineState::Running || destination < 0 || source < 0) return false;
    auto* dest = accumulators_.at(static_cast<std::size_t>(destination));
    const auto* src = accumulators_.at(static_cast<std::size_t>(source));
    if (!dest || !src) return false;
    DecimalALU alu;
    const auto result = alu.add(dest->value(), src->value());
    dest->set(result.value);
    dest->set_flags({result.overflow, result.value < 0});
    return true;
}
bool Machine::subtract(int destination, int source) noexcept {
    if (state_ != MachineState::Running || destination < 0 || source < 0) return false;
    auto* dest = accumulators_.at(static_cast<std::size_t>(destination));
    const auto* src = accumulators_.at(static_cast<std::size_t>(source));
    if (!dest || !src) return false;
    DecimalALU alu;
    const auto result = alu.subtract(dest->value(), src->value());
    dest->set(result.value);
    dest->set_flags({result.overflow, result.value < 0});
    return true;
}
bool Machine::multiply(int destination, int source) noexcept {
    if (state_ != MachineState::Running || destination < 0 || source < 0) return false;
    auto* dest = accumulators_.at(static_cast<std::size_t>(destination));
    const auto* src = accumulators_.at(static_cast<std::size_t>(source));
    if (!dest || !src) return false;
    DecimalALU alu;
    const auto result = alu.multiply(dest->value(), src->value());
    dest->set(result.value);
    dest->set_flags({result.overflow, result.value < 0});
    return true;
}
} // namespace eniac
