#include "eniac/control/program.hpp"
#include <utility>
namespace eniac {
void Program::append(Operation operation) { operations_.push_back(std::move(operation)); }
const std::vector<Operation>& Program::operations() const noexcept { return operations_; }
bool Program::empty() const noexcept { return operations_.empty(); }
} // namespace eniac
