#pragma once
#include "cpm22/disk.hpp"
#include <optional>
#include <string>
#include <vector>

namespace cpm22 {
// Small, explicit BDOS-inspired service facade. It is not ABI-compatible with CP/M.
class Bdos {
public:
    explicit Bdos(Disk& disk) : disk_(disk) {}
    [[nodiscard]] std::vector<DirectoryEntry> directory(std::string pattern = "*.*") const;
    [[nodiscard]] std::optional<std::string> read_file(std::string name, std::string& error) const;
    bool write_file(std::string name, const std::string& data, std::string& error);
    bool delete_file(std::string name, std::string& error);
    bool rename_file(std::string old_name, std::string new_name, std::string& error);
    bool copy_file(std::string source, std::string destination, std::string& error);
    bool set_user(unsigned user, std::string& error);
    bool set_drive(char drive, std::string& error);
    [[nodiscard]] Disk& disk() noexcept { return disk_; }
private:
    Disk& disk_;
};
} // namespace cpm22
