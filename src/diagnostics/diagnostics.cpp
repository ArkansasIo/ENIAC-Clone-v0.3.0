#include "eniac/diagnostics/diagnostics.hpp"
#include "eniac/core/machine.hpp"
namespace eniac {
std::vector<std::string> Diagnostics::inspect(const Machine& machine) const {
    std::vector<std::string> findings;
    if (machine.config().accumulator_count != AccumulatorBank::count) findings.emplace_back("Configured accumulator count differs from implemented bank size");
    if (machine.config().max_program_operations == 0) findings.emplace_back("Maximum program operation count is zero");
    return findings;
}
} // namespace eniac
