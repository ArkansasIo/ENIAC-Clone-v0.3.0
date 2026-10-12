#pragma once
#include "cpm22/bdos.hpp"
#include "cpm22/bios.hpp"
#include "cpm22/memory.hpp"
#include "cpm22/memory_editor.hpp"
#include "eniac_os/machine.hpp"
#include <string>
namespace cpm22 {
class Ccp {
public:
 Ccp(Bdos&,BiosConsole&,eniac_os::Machine&,Memory&,MemoryEditor&);
 int loop(); bool execute_line(const std::string&);
private:
 void help(); void directory(const std::string&); void run_program(const std::string&);
 [[nodiscard]] std::string prompt()const;
 Bdos& bdos_; BiosConsole& bios_; eniac_os::Machine& machine_; Memory& memory_; MemoryEditor& editor_;
};
}
