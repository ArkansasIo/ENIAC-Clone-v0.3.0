#pragma once
#include <cstdint>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace cpm22 {
struct DirectoryEntry {
    std::string name;
    std::uintmax_t bytes{};
};
class Disk {
public:
    explicit Disk(std::filesystem::path root = "disk");
    [[nodiscard]] char drive() const noexcept { return drive_; }
    [[nodiscard]] std::uint8_t user() const noexcept { return user_; }
    [[nodiscard]] const std::filesystem::path& root() const noexcept { return root_; }
    bool select_drive(char drive, std::string& error);
    bool select_user(unsigned user, std::string& error);
    [[nodiscard]] std::vector<DirectoryEntry> list(std::string pattern = "*.*") const;
    [[nodiscard]] std::optional<std::string> read(std::string name, std::string& error) const;
    bool write(std::string name, const std::string& contents, std::string& error);
    bool erase(std::string name, std::string& error);
    bool rename(std::string old_name, std::string new_name, std::string& error);
    bool copy(std::string source, std::string destination, std::string& error);
    [[nodiscard]] static std::optional<std::string> normalize_name(std::string name);
private:
    struct ResolvedName { char drive; std::string name; };
    [[nodiscard]] std::optional<ResolvedName> resolve_name(std::string name, std::string& error) const;
    [[nodiscard]] std::filesystem::path area_path(char drive, std::uint8_t user) const;
    [[nodiscard]] std::filesystem::path file_path(char drive, std::uint8_t user, const std::string& name) const;
    [[nodiscard]] static bool matches(std::string pattern, std::string name);
    std::filesystem::path root_;
    char drive_{'A'};
    std::uint8_t user_{0};
};
} // namespace cpm22
