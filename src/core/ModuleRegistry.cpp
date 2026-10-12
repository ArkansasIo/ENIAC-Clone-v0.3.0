#include "floppy52/core/ModuleRegistry.hpp"
#include <utility>
namespace floppy52::core {
types::Result ModuleRegistry::add(types::ModuleDescriptor descriptor) {
    if (descriptor.id.value.empty() || descriptor.name.empty())
        return {types::Status::InvalidArgument, "module id and name are required"};
    auto [it, inserted] = modules_.emplace(descriptor.id.value, std::move(descriptor));
    (void)it;
    if (!inserted) return {types::Status::InvalidArgument, "duplicate module id"};
    return {};
}
const types::ModuleDescriptor* ModuleRegistry::find(const std::string& id) const {
    auto it = modules_.find(id);
    return it == modules_.end() ? nullptr : &it->second;
}
std::vector<types::ModuleDescriptor> ModuleRegistry::all() const {
    std::vector<types::ModuleDescriptor> out;
    out.reserve(modules_.size());
    for (const auto& [id, descriptor] : modules_) { (void)id; out.push_back(descriptor); }
    return out;
}
}
