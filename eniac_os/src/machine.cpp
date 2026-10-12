#include "eniac_os/machine.hpp"
#include "eniac_os/program.hpp"
#include <sstream>
#include <stdexcept>
#include <utility>

namespace eniac_os {
Machine::Machine(Output output) : output_(std::move(output)) {}
void Machine::load(Program program) {
    program_ = std::move(program);
    reset();
}
void Machine::reset() {
    accumulators_.reset();
    pc_ = 0;
    state_ = MachineState::Ready;
    events_.clear();
}
void Machine::emit(std::string message) {
    events_.push_back({pc_, message});
    if (output_) output_(message);
}
StepResult Machine::step() {
    if (state_ == MachineState::Faulted) return {false, false, "machine is faulted; reset before continuing"};
    if (state_ == MachineState::Halted) return {true, true, "machine is halted"};
    if (pc_ >= program_.instructions.size()) {
        state_ = MachineState::Halted;
        emit("end of program");
        return {true, true, "end of program"};
    }
    const auto instruction = program_.instructions[pc_];
    state_ = MachineState::Running;
    try {
        switch (instruction.op) {
            case OpCode::Load: accumulators_.set(0, instruction.operand); ++pc_; break;
            case OpCode::Add: accumulators_.add(0, instruction.operand); ++pc_; break;
            case OpCode::Sub: accumulators_.subtract(0, instruction.operand); ++pc_; break;
            case OpCode::Mul: accumulators_.multiply(0, instruction.operand); ++pc_; break;
            case OpCode::Div: accumulators_.divide(0, instruction.operand); ++pc_; break;
            case OpCode::Store:
                accumulators_.set(static_cast<std::size_t>(instruction.operand), accumulators_.get(0));
                ++pc_;
                break;
            case OpCode::Print:
                emit("A0 = " + std::to_string(accumulators_.get(0)));
                ++pc_;
                break;
            case OpCode::Jump:
                if (static_cast<std::uint64_t>(instruction.operand) >= program_.instructions.size())
                    throw std::out_of_range("jump target is outside program");
                pc_ = static_cast<std::size_t>(instruction.operand);
                break;
            case OpCode::JumpIfNonZero:
                if (accumulators_.get(0) != 0) {
                    if (static_cast<std::uint64_t>(instruction.operand) >= program_.instructions.size())
                        throw std::out_of_range("jump target is outside program");
                    pc_ = static_cast<std::size_t>(instruction.operand);
                } else ++pc_;
                break;
            case OpCode::Halt:
                state_ = MachineState::Halted;
                emit("HALT instruction");
                return {true, true, "HALT"};
        }
    } catch (const std::exception& error) {
        state_ = MachineState::Faulted;
        const auto message = std::string("fault at source line ") + std::to_string(instruction.line) + ": " + error.what();
        emit(message);
        return {false, false, message};
    }
    if (pc_ >= program_.instructions.size()) {
        state_ = MachineState::Halted;
        emit("end of program");
        return {true, true, "end of program"};
    }
    return {true, false, "step complete"};
}
StepResult Machine::run(std::size_t max_steps) {
    for (std::size_t i = 0; i < max_steps; ++i) {
        auto result = step();
        if (!result.ok || result.halted) return result;
    }
    state_ = MachineState::Faulted;
    emit("execution step limit reached");
    return {false, false, "execution step limit reached"};
}
std::string Machine::status() const {
    std::ostringstream out;
    out << "program=" << program_.name << " pc=" << pc_ << " state=";
    switch (state_) {
        case MachineState::Ready: out << "ready"; break;
        case MachineState::Running: out << "running"; break;
        case MachineState::Halted: out << "halted"; break;
        case MachineState::Faulted: out << "faulted"; break;
    }
    return out.str();
}
} // namespace eniac_os
