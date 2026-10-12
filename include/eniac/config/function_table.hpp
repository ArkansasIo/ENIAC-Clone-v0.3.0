#pragma once

#include <optional>
#include <string>
#include <unordered_map>

namespace eniac {

class FunctionTable {
public:
    void set(std::string name, long long value);
    [[nodiscard]] std::optional<long long> get(const std::string& name) const;
    [[nodiscard]] bool contains(const std::string& name) const;

private:
    std::unordered_map<std::string, long long> values_;
};

} // namespace eniac
