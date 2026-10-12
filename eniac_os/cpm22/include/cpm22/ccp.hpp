#pragma once
#include "cpm22/bdos.hpp"
#include "cpm22/bios.hpp"
#include "eniac_os/machine.hpp"
#include <string>

namespace cpm22 {
// Command Console Processor (CCP)-style line interpreter.
class Ccp {
public:
    Ccp(Bdos& bdos, BiosConsole& bios, eniac_os::Machine& machine);
    int loop();
    bool execute_line(const std::string& line);
private:
    void help();
    void directory(const std::string& pattern);
    void run_program(const std::string& name);
    [[nodiscard]] std::string prompt() const;
    Bdos& bdos_;
    BiosConsole& bios_;
    eniac_os::Machine& machine_;
};
} // namespace cpm22
