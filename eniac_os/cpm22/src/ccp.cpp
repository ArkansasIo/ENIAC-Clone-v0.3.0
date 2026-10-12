#include "cpm22/ccp.hpp"
#include "eniac_os/program.hpp"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <string_view>

namespace cpm22 {
namespace {
std::string upper(std::string value) {
    for (char& ch : value) ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    return value;
}
std::string trim(std::string value) {
    const auto first = value.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    return value.substr(first, value.find_last_not_of(" \t\r\n") - first + 1);
}
}
Ccp::Ccp(Bdos& bdos, BiosConsole& bios, eniac_os::Machine& machine)
    : bdos_(bdos), bios_(bios), machine_(machine) {}
std::string Ccp::prompt() const {
    return std::string(1, bdos_.disk().drive()) + "> ";
}
void Ccp::help() {
    bios_.write("ENIAC CP/M 2.2-style command set\n"
                "  DIR [pattern]       list files (8.3 names; wildcards supported)\n"
                "  TYPE file           display a text file\n"
                "  ERA file            erase a file\n"
                "  REN new=old         rename a file\n"
                "  COPY source dest    copy a file\n"
                "  USER 0..15          select a user area\n"
                "  A: B: C: D:         select virtual drive\n"
                "  RUN file.EPR        run an ENIAC program file\n"
                "  STAT                show current drive/user and file totals\n"
                "  VER, ECHO, CLS, HELP, EXIT\n"
                "Drive data is stored beneath ./disk/<drive>/USERxx.\n");
}
void Ccp::directory(const std::string& pattern) {
    const auto entries = bdos_.directory(pattern.empty() ? "*.*" : pattern);
    std::uintmax_t total = 0;
    bios_.write("Directory of " + std::string(1, bdos_.disk().drive()) + ": user " +
                std::to_string(bdos_.disk().user()) + "\n");
    for (const auto& entry : entries) {
        std::ostringstream row;
        row << std::left << std::setw(12) << entry.name << std::right << std::setw(8) << entry.bytes << " bytes\n";
        bios_.write(row.str()); total += entry.bytes;
    }
    bios_.write(std::to_string(entries.size()) + " file(s), " + std::to_string(total) + " bytes\n");
}
void Ccp::run_program(const std::string& name) {
    std::string error;
    auto source = bdos_.read_file(name, error);
    if (!source) { bios_.write(error + "\n"); return; }
    std::istringstream input(*source);
    auto parsed = eniac_os::parse_program(input, name);
    if (!parsed.ok()) {
        for (const auto& issue : parsed.errors)
            bios_.write("Program line " + std::to_string(issue.line) + ": " + issue.message + "\n");
        return;
    }
    machine_.load(std::move(parsed.program));
    bios_.write("Loaded " + std::to_string(machine_.program().instructions.size()) + " instruction(s).\n");
    const auto result = machine_.run();
    bios_.write(result.message + "\n");
}
int Ccp::loop() {
    bios_.write("ENIAC CP/M 2.2-style OS 0.1\n"
                "CCP-like shell / BDOS-like file services / BIOS-like console\n"
                "Educational compatibility layer; not Digital Research CP/M. Type HELP.\n");
    std::string line;
    while (bios_.write(prompt()), bios_.read_line(line)) {
        if (!execute_line(line)) break;
    }
    return 0;
}
bool Ccp::execute_line(const std::string& raw) {
    const std::string line = trim(raw);
    if (line.empty()) return true;
    const auto split = line.find_first_of(" \t");
    const std::string command = upper(line.substr(0, split));
    const std::string args = split == std::string::npos ? "" : trim(line.substr(split + 1));
    std::string error;
    if (command == "EXIT" || command == "BYE" || command == "QUIT") return false;
    if (command == "HELP" || command == "?") { help(); return true; }
    if (command == "VER") { bios_.write("ENIAC CP/M-style OS 0.1 (CP/M-inspired, not binary-compatible)\n"); return true; }
    if (command == "CLS") { bios_.clear_screen(); return true; }
    if (command == "ECHO") { bios_.write(args + "\n"); return true; }
    if (command == "DIR") { directory(args); return true; }
    if (command == "USER") {
        unsigned user = 0;
        try {
            std::size_t used = 0; const auto parsed = std::stoul(args, &used);
            if (used != args.size()) throw std::invalid_argument("trailing");
            user = static_cast<unsigned>(parsed);
        } catch (...) { bios_.write("Usage: USER 0..15\n"); return true; }
        if (bdos_.set_user(user, error)) bios_.write("Current user area: " + std::to_string(user) + "\n");
        else bios_.write(error + "\n");
        return true;
    }
    if (command.size() == 2 && command[1] == ':') {
        if (bdos_.set_drive(command[0], error)) bios_.write("Current drive: " + command + "\n");
        else bios_.write(error + "\n");
        return true;
    }
    if (command == "TYPE") {
        if (args.empty()) { bios_.write("Usage: TYPE filename\n"); return true; }
        auto contents = bdos_.read_file(args, error);
        if (contents) { bios_.write(*contents); if (contents->empty() || contents->back() != '\n') bios_.newline(); }
        else bios_.write(error + "\n");
        return true;
    }
    if (command == "ERA" || command == "ERASE" || command == "DEL") {
        if (args.empty()) { bios_.write("Usage: ERA filename\n"); return true; }
        if (bdos_.delete_file(args, error)) bios_.write("Erased " + args + "\n");
        else bios_.write(error + "\n");
        return true;
    }
    if (command == "REN") {
        const auto equal = args.find('=');
        if (equal == std::string::npos) { bios_.write("Usage: REN newname=oldname\n"); return true; }
        const auto new_name = trim(args.substr(0, equal));
        const auto old_name = trim(args.substr(equal + 1));
        if (bdos_.rename_file(old_name, new_name, error)) bios_.write("Renamed " + old_name + " to " + new_name + "\n");
        else bios_.write(error + "\n");
        return true;
    }
    if (command == "COPY") {
        std::istringstream stream(args); std::string source, destination, extra;
        if (!(stream >> source >> destination) || (stream >> extra)) { bios_.write("Usage: COPY source destination\n"); return true; }
        if (bdos_.copy_file(source, destination, error)) bios_.write("Copied " + source + " to " + destination + "\n");
        else bios_.write(error + "\n");
        return true;
    }
    if (command == "RUN") {
        if (args.empty()) { bios_.write("Usage: RUN program.EPR\n"); return true; }
        run_program(args); return true;
    }
    if (command == "STAT") {
        const auto entries = bdos_.directory();
        std::uintmax_t bytes = 0; for (const auto& entry : entries) bytes += entry.bytes;
        bios_.write("Drive " + std::string(1, bdos_.disk().drive()) + ":, user " +
                    std::to_string(bdos_.disk().user()) + ", " + std::to_string(entries.size()) +
                    " file(s), " + std::to_string(bytes) + " bytes in current area.\n");
        return true;
    }
    bios_.write("Bad command or filename: " + command + " (type HELP)\n");
    return true;
}
} // namespace cpm22
