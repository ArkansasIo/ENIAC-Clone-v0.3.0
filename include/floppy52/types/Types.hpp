#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace floppy52::types {
using Byte = std::uint8_t;
using Word = std::uint16_t;
using DWord = std::uint32_t;
using QWord = std::uint64_t;
enum class Status : Byte { Ok, InvalidArgument, NotFound, IoError, Unsupported };
struct Result {
    Status status{Status::Ok};
    std::string message{"ok"};
    explicit operator bool() const noexcept { return status == Status::Ok; }
};
struct AddressRange {
    DWord base{};
    DWord length{};
    bool contains(DWord address) const noexcept {
        return address >= base && static_cast<QWord>(address) < static_cast<QWord>(base) + length;
    }
};
template<class T> struct ArrayView {
    std::vector<T> values;
    std::size_t size() const noexcept { return values.size(); }
    bool empty() const noexcept { return values.empty(); }
};
struct ModuleId { std::string value; friend bool operator==(const ModuleId&, const ModuleId&) = default; };
struct ModuleDescriptor {
    ModuleId id;
    std::string name;
    std::string version;
    std::vector<ModuleId> submodules;
};
}
