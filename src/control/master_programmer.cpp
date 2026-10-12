#include "eniac/control/master_programmer.hpp"
namespace eniac {
MasterProgrammer::MasterProgrammer(std::size_t repetitions) : repetitions_(repetitions) {}
bool MasterProgrammer::has_next() const noexcept { return current_ < repetitions_; }
void MasterProgrammer::advance() noexcept { if (has_next()) ++current_; }
void MasterProgrammer::reset() noexcept { current_ = 0; }
std::size_t MasterProgrammer::current_iteration() const noexcept { return current_; }
} // namespace eniac
