#include "cpm22/disk.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iterator>
#include <system_error>

namespace cpm22 {
namespace {
std::string upper(std::string value) {
    for (char& ch : value) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    return value;
}
bool wildcard_match(const std::string& pattern, const std::string& value, std::size_t p = 0, std::size_t v = 0) {
    if (p == pattern.size()) return v == value.size();
    if (pattern[p] == '*') {
        for (std::size_t i = v; i <= value.size(); ++i)
            if (wildcard_match(pattern, value, p + 1, i)) return true;
        return false;
    }
    return v < value.size() && (pattern[p] == '?' || pattern[p] == value[v]) &&
           wildcard_match(pattern, value, p + 1, v + 1);
}
}
Disk::Disk(std::filesystem::path root) : root_(std::move(root)) {
    std::error_code ec;
    for (char d = 'A'; d <= 'D'; ++d)
        std::filesystem::create_directories(area_path(d, 0), ec);
}
std::optional<std::string> Disk::normalize_name(std::string name) {
    name = upper(std::move(name));
    if (name.empty() || name.find_first_of("/\\:") != std::string::npos) return std::nullopt;
    const auto dot = name.find('.');
    const std::string base = name.substr(0, dot);
    const std::string ext = dot == std::string::npos ? "" : name.substr(dot + 1);
    if (base.empty() || base.size() > 8 || ext.size() > 3 ||
        (dot != std::string::npos && (ext.empty() || name.find('.', dot + 1) != std::string::npos)))
        return std::nullopt;
    const auto valid = [](const std::string& part) {
        return std::all_of(part.begin(), part.end(), [](unsigned char c) {
            return std::isalnum(c) || c == '_' || c == '$' || c == '#' || c == '@' || c == '!' || c == '%' || c == '&' || c == '-' || c == '\'' || c == '(' || c == ')' || c == '{' || c == '}' || c == '~' || c == '^';
        });
    };
    if (!valid(base) || !valid(ext)) return std::nullopt;
    return ext.empty() ? base : base + "." + ext;
}
std::optional<Disk::ResolvedName> Disk::resolve_name(std::string name, std::string& error) const {
    char drive = drive_;
    const auto colon = name.find(':');
    if (colon != std::string::npos) {
        if (colon != 1) { error = "Invalid drive-qualified filename."; return std::nullopt; }
        drive = static_cast<char>(std::toupper(static_cast<unsigned char>(name[0])));
        name.erase(0, 2);
        if (drive < 'A' || drive > 'D') { error = "Drive must be A: through D:."; return std::nullopt; }
    }
    auto normalized = normalize_name(std::move(name));
    if (!normalized) { error = "Filename must use CP/M 8.3 format (for example FILE.TXT)."; return std::nullopt; }
    return ResolvedName{drive, *normalized};
}
std::filesystem::path Disk::area_path(char drive, std::uint8_t user) const {
    char area[8]{'U','S','E','R','0','0','\0','\0'};
    area[4] = static_cast<char>('0' + (user / 10));
    area[5] = static_cast<char>('0' + (user % 10));
    return root_ / std::string(1, drive) / area;
}
std::filesystem::path Disk::file_path(char drive, std::uint8_t user, const std::string& name) const {
    return area_path(drive, user) / name;
}
bool Disk::select_drive(char drive, std::string& error) {
    drive = static_cast<char>(std::toupper(static_cast<unsigned char>(drive)));
    if (drive < 'A' || drive > 'D') { error = "Drive must be A: through D:."; return false; }
    std::error_code ec;
    std::filesystem::create_directories(area_path(drive, user_), ec);
    if (ec) { error = "Cannot initialize drive area: " + ec.message(); return false; }
    drive_ = drive; return true;
}
bool Disk::select_user(unsigned user, std::string& error) {
    if (user > 15) { error = "User number must be in the range 0..15."; return false; }
    std::error_code ec;
    std::filesystem::create_directories(area_path(drive_, static_cast<std::uint8_t>(user)), ec);
    if (ec) { error = "Cannot initialize user area: " + ec.message(); return false; }
    user_ = static_cast<std::uint8_t>(user); return true;
}
bool Disk::matches(std::string pattern, std::string name) {
    pattern = upper(std::move(pattern)); name = upper(std::move(name));
    if (pattern == "*" || pattern == "*.*") return true;
    if (pattern.find('.') == std::string::npos) pattern += ".*";
    return wildcard_match(pattern, name);
}
std::vector<DirectoryEntry> Disk::list(std::string pattern) const {
    std::vector<DirectoryEntry> result;
    std::error_code ec;
    const auto dir = area_path(drive_, user_);
    std::filesystem::create_directories(dir, ec);
    for (std::filesystem::directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec)) {
        if (!it->is_regular_file(ec)) continue;
        const auto name = it->path().filename().string();
        if (matches(pattern, name)) result.push_back({name, it->file_size(ec)});
    }
    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) { return a.name < b.name; });
    return result;
}
std::optional<std::string> Disk::read(std::string name, std::string& error) const {
    auto resolved = resolve_name(std::move(name), error);
    if (!resolved) return std::nullopt;
    std::ifstream input(file_path(resolved->drive, user_, resolved->name), std::ios::binary);
    if (!input) { error = "File not found: " + resolved->name; return std::nullopt; }
    return std::string(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
}
bool Disk::write(std::string name, const std::string& contents, std::string& error) {
    auto resolved = resolve_name(std::move(name), error);
    if (!resolved) return false;
    std::error_code ec;
    std::filesystem::create_directories(area_path(resolved->drive, user_), ec);
    if (ec) { error = "Cannot initialize drive area: " + ec.message(); return false; }
    std::ofstream output(file_path(resolved->drive, user_, resolved->name), std::ios::binary | std::ios::trunc);
    if (!output) { error = "Cannot write file: " + resolved->name; return false; }
    output.write(contents.data(), static_cast<std::streamsize>(contents.size()));
    if (!output) { error = "Write failed: " + resolved->name; return false; }
    return true;
}
bool Disk::erase(std::string name, std::string& error) {
    auto resolved = resolve_name(std::move(name), error);
    if (!resolved) return false;
    std::error_code ec;
    const bool removed = std::filesystem::remove(file_path(resolved->drive, user_, resolved->name), ec);
    if (ec || !removed) { error = "Cannot erase file (not found or inaccessible): " + resolved->name; return false; }
    return true;
}
bool Disk::rename(std::string old_name, std::string new_name, std::string& error) {
    auto old_resolved = resolve_name(std::move(old_name), error);
    if (!old_resolved) return false;
    auto new_resolved = resolve_name(std::move(new_name), error);
    if (!new_resolved) return false;
    if (old_resolved->drive != new_resolved->drive) { error = "REN cannot move files between drives."; return false; }
    std::error_code ec;
    if (!std::filesystem::exists(file_path(old_resolved->drive, user_, old_resolved->name), ec)) {
        error = "Source file not found: " + old_resolved->name; return false;
    }
    if (std::filesystem::exists(file_path(new_resolved->drive, user_, new_resolved->name), ec)) {
        error = "Destination already exists: " + new_resolved->name; return false;
    }
    std::filesystem::rename(file_path(old_resolved->drive, user_, old_resolved->name),
                            file_path(new_resolved->drive, user_, new_resolved->name), ec);
    if (ec) { error = "Rename failed: " + ec.message(); return false; }
    return true;
}
bool Disk::copy(std::string source, std::string destination, std::string& error) {
    auto data = read(std::move(source), error);
    if (!data) return false;
    auto resolved = resolve_name(destination, error);
    if (!resolved) return false;
    std::error_code ec;
    if (std::filesystem::exists(file_path(resolved->drive, user_, resolved->name), ec)) {
        error = "Destination already exists: " + resolved->name; return false;
    }
    return write(std::move(destination), *data, error);
}
} // namespace cpm22
