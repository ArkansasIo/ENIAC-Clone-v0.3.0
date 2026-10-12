#pragma once
#include "floppy52/types/Types.hpp"
#include <map>
#include <string>
#include <vector>
namespace floppy52::core {
class ModuleRegistry {
public:
    [[nodiscard]] types::Result add(types::ModuleDescriptor descriptor);
    [[nodiscard]] const types::ModuleDescriptor* find(const std::string& id) const;
    [[nodiscard]] std::vector<types::ModuleDescriptor> all() const;
private:
    std::map<std::string, types::ModuleDescriptor, std::less<>> modules_;
};
}
