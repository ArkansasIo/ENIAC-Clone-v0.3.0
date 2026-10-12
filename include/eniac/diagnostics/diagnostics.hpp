#pragma once
#include <string>
#include <vector>
namespace eniac {
class Machine;
class Diagnostics {
public:
    [[nodiscard]] std::vector<std::string> inspect(const Machine& machine) const;
};
} // namespace eniac
