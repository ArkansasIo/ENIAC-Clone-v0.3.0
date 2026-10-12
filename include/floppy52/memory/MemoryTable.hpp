#pragma once
#include "floppy52/types/Types.hpp"
#include <optional>
#include <vector>
namespace floppy52::memory {
struct Cell { types::DWord address{}; types::Byte value{}; bool initialized{}; };
class MemoryTable {
public:
    explicit MemoryTable(std::size_t cellCount = 1024);
    [[nodiscard]] types::Result write(types::DWord address, types::Byte value);
    [[nodiscard]] std::optional<types::Byte> read(types::DWord address) const;
    [[nodiscard]] const std::vector<Cell>& cells() const noexcept { return cells_; }
private:
    std::vector<Cell> cells_;
};
}
