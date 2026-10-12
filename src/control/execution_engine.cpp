#include "eniac/control/execution_engine.hpp"
#include "eniac/core/machine.hpp"
namespace eniac {
bool ExecutionEngine::execute(Machine& machine, const Program& program) const {
    if (program.operations().size() > machine.config().max_program_operations || machine.state() != MachineState::Running) return false;
    for (const auto& operation : program.operations()) {
        bool ok = false;
        switch (operation.code) {
        case OperationCode::Add: ok = machine.add(operation.destination, operation.source); break;
        case OperationCode::Subtract: ok = machine.subtract(operation.destination, operation.source); break;
        case OperationCode::Multiply: ok = machine.multiply(operation.destination, operation.source); break;
        case OperationCode::LoadConstant: ok = machine.load_value(static_cast<std::size_t>(operation.destination), operation.constant); break;
        }
        if (!ok) return false;
        machine.tick();
    }
    return true;
}
} // namespace eniac
