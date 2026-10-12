#include "cpm22/bdos.hpp"
namespace cpm22 {
std::vector<DirectoryEntry> Bdos::directory(std::string pattern) const { return disk_.list(std::move(pattern)); }
std::optional<std::string> Bdos::read_file(std::string name, std::string& error) const { return disk_.read(std::move(name), error); }
bool Bdos::write_file(std::string name, const std::string& data, std::string& error) { return disk_.write(std::move(name), data, error); }
bool Bdos::delete_file(std::string name, std::string& error) { return disk_.erase(std::move(name), error); }
bool Bdos::rename_file(std::string old_name, std::string new_name, std::string& error) { return disk_.rename(std::move(old_name), std::move(new_name), error); }
bool Bdos::copy_file(std::string source, std::string destination, std::string& error) { return disk_.copy(std::move(source), std::move(destination), error); }
bool Bdos::set_user(unsigned user, std::string& error) { return disk_.select_user(user, error); }
bool Bdos::set_drive(char drive, std::string& error) { return disk_.select_drive(drive, error); }
} // namespace cpm22
