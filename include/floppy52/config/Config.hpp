#pragma once
#include <cstddef>
#include <string>
#include <map>
namespace floppy52::config {
struct Config {
    std::string productName{"FLOPPY 5.2"};
    std::string bootMessage{"FLOPPY 5.2 SYSTEM START"};
    std::size_t simulatedMemoryCells{1024};
    std::map<std::string, std::string> options;
};
[[nodiscard]] Config defaults();
[[nodiscard]] bool loadKeyValueFile(const std::string& path, Config& config, std::string& error);
}
