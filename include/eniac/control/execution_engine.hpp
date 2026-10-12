#pragma once

#include "eniac/control/program.hpp"

namespace eniac {

class Machine;

class ExecutionEngine {
public:
    [[nodiscard]] bool execute(Machine& machine, const Program& program) const;
};

} // namespace eniac
