#include "floppy52/config/Config.hpp"
#include <fstream>
namespace floppy52::config {
Config defaults() { return {}; }
bool loadKeyValueFile(const std::string& path, Config& config, std::string& error) {
    std::ifstream in(path);
    if (!in) { error = "cannot open config file: " + path; return false; }
    std::string line; std::size_t lineNo = 0;
    auto trim = [](std::string& s) {
        auto b = s.find_first_not_of(" \t\r");
        auto e = s.find_last_not_of(" \t\r");
        s = b == std::string::npos ? "" : s.substr(b, e - b + 1);
    };
    while (std::getline(in, line)) {
        ++lineNo;
        auto first = line.find_first_not_of(" \t\r");
        if (first == std::string::npos || line[first] == '#' || line[first] == ';') continue;
        auto split = line.find('=');
        if (split == std::string::npos) { error = "expected key=value at line " + std::to_string(lineNo); return false; }
        auto key = line.substr(0, split), value = line.substr(split + 1);
        trim(key); trim(value);
        if (key == "product_name") config.productName = value;
        else if (key == "boot_message") config.bootMessage = value;
        else config.options[key] = value;
    }
    return true;
}
}
