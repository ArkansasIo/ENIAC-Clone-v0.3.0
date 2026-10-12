#pragma once
#include <cstddef>
#include "eniac/core/accumulator_bank.hpp"
#include "eniac/core/machine_clock.hpp"
#include "eniac/core/machine_config.hpp"
#include "eniac/core/types.hpp"
#include "eniac/io/event_log.hpp"
namespace eniac {
class Machine {
public:
    explicit Machine(MachineConfig config = {});
    [[nodiscard]] MachineState state() const noexcept;
    [[nodiscard]] const MachineConfig& config() const noexcept;
    [[nodiscard]] AccumulatorBank& accumulators() noexcept;
    [[nodiscard]] const AccumulatorBank& accumulators() const noexcept;
    [[nodiscard]] MachineClock& clock() noexcept;
    [[nodiscard]] const MachineClock& clock() const noexcept;
    [[nodiscard]] EventLog& events() noexcept;
    [[nodiscard]] const EventLog& events() const noexcept;
    [[nodiscard]] bool start();
    [[nodiscard]] bool stop();
    [[nodiscard]] bool reset();
    void tick() noexcept;
    [[nodiscard]] bool load_value(std::size_t index, long long value) noexcept;
    [[nodiscard]] bool add(int destination, int source) noexcept;
    [[nodiscard]] bool subtract(int destination, int source) noexcept;
    [[nodiscard]] bool multiply(int destination, int source) noexcept;
private:
    MachineConfig config_;
    MachineState state_{MachineState::Stopped};
    AccumulatorBank accumulators_{};
    MachineClock clock_{};
    EventLog events_{};
};
} // namespace eniac
