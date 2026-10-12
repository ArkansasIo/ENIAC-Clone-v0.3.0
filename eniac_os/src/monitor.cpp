#include "eniac_os/monitor.hpp"
#include "eniac_os/program.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace eniac_os {
Monitor::Monitor(Machine& machine, std::istream& input, std::ostream& output)
    : machine_(machine), input_(input), output_(output) {}
void Monitor::print_help() const {
    output_ << "Commands:\n"
            << "  help              show commands\n"
            << "  load PATH         load a .epr program\n"
            << "  list              list loaded instructions\n"
            << "  step              execute one instruction\n"
            << "  run               execute until halt or fault\n"
            << "  regs              show accumulator bank\n"
            << "  status            show machine state\n"
            << "  reset             reset registers and program counter\n"
            << "  quit              exit monitor\n";
}
int Monitor::loop(const std::filesystem::path& initial_program) {
    output_ << "ENIAC Program OS 0.1 — educational monitor\n"
            << "Type 'help' for commands. This is a modern simulator layer, not a historical ENIAC OS.\n";
    if (!initial_program.empty()) {
        auto parsed = load_program(initial_program);
        if (!parsed.ok()) {
            for (const auto& error : parsed.errors)
                output_ << "load error line " << error.line << ": " << error.message << '\n';
        } else {
            machine_.load(std::move(parsed.program));
            output_ << "Loaded " << machine_.program().instructions.size() << " instructions.\n";
        }
    }
    std::string line;
    while (output_ << "eniac-os> " && std::getline(input_, line)) {
        if (!execute_line(line)) break;
    }
    return 0;
}
bool Monitor::execute_line(const std::string& line) {
    std::istringstream command_line(line);
    std::string command;
    command_line >> command;
    if (command.empty()) return true;
    if (command == "quit" || command == "exit") return false;
    if (command == "help") { print_help(); return true; }
    if (command == "status") { output_ << machine_.status() << '\n'; return true; }
    if (command == "regs") { output_ << machine_.accumulators().describe(); return true; }
    if (command == "reset") { machine_.reset(); output_ << "Machine reset.\n"; return true; }
    if (command == "list") {
        const auto& program = machine_.program();
        for (std::size_t i = 0; i < program.instructions.size(); ++i) {
            const auto& inst = program.instructions[i];
            output_ << i << ": " << opcode_name(inst.op);
            if (inst.op != OpCode::Print && inst.op != OpCode::Halt) output_ << ' ' << inst.operand;
            output_ << "  ; source line " << inst.line << '\n';
        }
        return true;
    }
    if (command == "load") {
        std::string path;
        if (!(command_line >> path)) { output_ << "Usage: load PATH\n"; return true; }
        auto parsed = load_program(path);
        if (!parsed.ok()) {
            for (const auto& error : parsed.errors)
                output_ << "line " << error.line << ": " << error.message << '\n';
        } else {
            machine_.load(std::move(parsed.program));
            output_ << "Loaded " << machine_.program().instructions.size() << " instructions.\n";
        }
        return true;
    }
    if (command == "step") {
        const auto result = machine_.step();
        output_ << result.message << '\n';
        return true;
    }
    if (command == "run") {
        const auto result = machine_.run();
        output_ << result.message << '\n';
        return true;
    }
    output_ << "Unknown command: " << command << " (type help)\n";
    return true;
}
} // namespace eniac_os
