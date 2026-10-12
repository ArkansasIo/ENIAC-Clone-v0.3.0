#include "eniac/config/function_table.hpp"
#include <utility>
namespace eniac {
void FunctionTable::set(std::string name, long long value) { values_.insert_or_assign(std::move(name), value); }
std::optional<long long> FunctionTable::get(const std::string& name) const { const auto it = values_.find(name); return it == values_.end() ? std::nullopt : std::optional<long long>{it->second}; }
bool FunctionTable::contains(const std::string& name) const { return values_.contains(name); }
} // namespace eniac
