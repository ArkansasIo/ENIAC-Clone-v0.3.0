#include "floppy52/config/Config.hpp"
#include "floppy52/core/ModuleRegistry.hpp"
#include "floppy52/memory/MemoryTable.hpp"
#include <iomanip>
#include <iostream>
#include <string>
using namespace floppy52;
static void showHelp() {
    std::cout << "FLOPPY 5.2 Developer Kit\nCommands: help | modules | memory | types | load-config <path> | quit\n";
}
int main(int argc, char** argv) {
    auto cfg = config::defaults();
    core::ModuleRegistry registry;
    (void)registry.add({{"core"}, "Core Runtime", "5.2.0", {{"types"}, {"memory"}}});
    (void)registry.add({{"types"}, "Type System", "5.2.0", {}});
    (void)registry.add({{"memory"}, "Memory Table Simulator", "5.2.0", {}});
    memory::MemoryTable memory(cfg.simulatedMemoryCells);
    std::cout << "========================================\n  FLOPPY 5.2 :: DEV TOOL / SDK CONSOLE\n========================================\n";
    if (argc > 1 && std::string(argv[1]) == "--version") { std::cout << "5.2.0\n"; return 0; }
    showHelp();
    std::string line;
    while (std::cout << "F52> " && std::getline(std::cin, line)) {
        if (line == "quit" || line == "exit") break;
        if (line == "help") showHelp();
        else if (line == "modules") {
            for (const auto& m : registry.all()) {
                std::cout << "- " << m.id.value << " :: " << m.name << " v" << m.version << '\n';
                for (const auto& sub : m.submodules) std::cout << "    submodule: " << sub.value << '\n';
            }
        } else if (line == "memory") {
            std::cout << "Simulated cells: " << memory.cells().size() << "\n";
            for (std::size_t i = 0; i < memory.cells().size() && i < 16; ++i) {
                const auto& c = memory.cells()[i];
                std::cout << std::hex << std::setw(4) << std::setfill('0') << c.address << " | "
                          << (c.initialized ? static_cast<int>(c.value) : 0)
                          << (c.initialized ? "" : " (unset)") << '\n';
            }
            std::cout << std::dec;
        } else if (line == "types") {
            std::cout << "Byte=8-bit, Word=16-bit, DWord=32-bit, QWord=64-bit\n"
                      << "Status: Ok, InvalidArgument, NotFound, IoError, Unsupported\n";
        } else if (line.rfind("load-config ", 0) == 0) {
            std::string error;
            if (config::loadKeyValueFile(line.substr(12), cfg, error)) std::cout << "Loaded config: " << cfg.productName << '\n';
            else std::cout << "Config error: " << error << '\n';
        } else std::cout << "Unknown command. Type 'help'.\n";
    }
    std::cout << "FLOPPY 5.2 session ended.\n";
}
