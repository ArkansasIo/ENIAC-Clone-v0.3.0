#pragma once
#include <cstdint>
#include <string>
namespace floppy52::sdk::disk {
struct Geometry {
    std::uint16_t cylinders{80};
    std::uint8_t heads{2};
    std::uint8_t sectorsPerTrack{18};
    std::uint16_t bytesPerSector{512};
};
struct DiskInfo {
    std::string label{"FLOPPY52"};
    Geometry geometry{};
    std::uint64_t capacityBytes() const {
        return static_cast<std::uint64_t>(geometry.cylinders) * geometry.heads *
               geometry.sectorsPerTrack * geometry.bytesPerSector;
    }
};
}
