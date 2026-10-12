#pragma once
#include "eniac_os/accumulator.hpp"
#include "eniac_os/instruction.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace eniac_os {
enum class MachineState { Ready, Running, Halted, Faulted };
struct MachineEvent {
    std::size_t pc{0};
    std::string message;
};
struct StepResult {
    bool ok{true};
    bool halted{false};
    std::string message;
};

class Machine {
public:
    using Output = std::function<void(const std::string&)>;
    explicit Machine(Output output = {});
    void load(Program program);
    void reset();
    [[nodiscard]] StepResult step();
    [[nodiscard]] StepResult run(std::size_t max_steps = 100000);
    [[nodiscard]] const Program& program() const noexcept { return program_; }
    [[nodiscard]] const AccumulatorBank& accumulators() const noexcept { return accumulators_; }
    [[nodiscard]] std::size_t pc() const noexcept { return pc_; }
    [[nodiscard]] MachineState state() const noexcept { return state_; }
    [[nodiscard]] const std::vector<MachineEvent>& events() const noexcept { return events_; }
    [[nodiscard]] std::string status() const;
private:
    void emit(std::string message);
    Output output_;
    Program program_;
    AccumulatorBank accumulators_;
    std::size_t pc_{0};
    MachineState state_{MachineState::Ready};
    std::vector<MachineEvent> events_;
};
} // namespace eniac_os
