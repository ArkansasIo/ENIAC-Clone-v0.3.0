#include "floppy52/core/ModuleRegistry.hpp"
#include "floppy52/memory/MemoryTable.hpp"
#include <cassert>
int main() {
    floppy52::core::ModuleRegistry registry;
    auto ok = registry.add({{"demo"}, "Demo Module", "1.0", {}});
    assert(ok);
    assert(registry.find("demo") != nullptr);
    assert(!registry.add({{"demo"}, "Duplicate", "1.0", {}}));
    floppy52::memory::MemoryTable memory(16);
    assert(memory.write(3, 0xA5));
    assert(memory.read(3).has_value());
    assert(memory.read(3).value() == 0xA5);
    assert(!memory.write(99, 1));
    assert(!memory.read(99).has_value());
}
