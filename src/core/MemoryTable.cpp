#include "floppy52/memory/MemoryTable.hpp"
namespace floppy52::memory {
MemoryTable::MemoryTable(std::size_t cellCount) {
    cells_.reserve(cellCount);
    for (std::size_t i = 0; i < cellCount; ++i)
        cells_.push_back(Cell{static_cast<types::DWord>(i), 0, false});
}
types::Result MemoryTable::write(types::DWord address, types::Byte value) {
    if (address >= cells_.size()) return {types::Status::InvalidArgument, "address outside simulated memory"};
    cells_[address].value = value; cells_[address].initialized = true; return {};
}
std::optional<types::Byte> MemoryTable::read(types::DWord address) const {
    if (address >= cells_.size() || !cells_[address].initialized) return std::nullopt;
    return cells_[address].value;
}
}
