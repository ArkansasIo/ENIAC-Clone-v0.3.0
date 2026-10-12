#pragma once
#include <cstddef>
#include <string>
namespace eniac {
struct MachineConfig {
    std::string name{"ENIAC educational simulator"};
    std::size_t accumulator_count{20};
    std::size_t max_program_operations{100000};
};
} // namespace eniac
