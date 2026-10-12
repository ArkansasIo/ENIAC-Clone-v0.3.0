#include "eniac_os/machine.hpp"
#include "eniac_os/monitor.hpp"
#include <filesystem>
#include <iostream>

int main(int argc, char** argv) {
    eniac_os::Machine machine([](const std::string& message) {
        std::cout << "[machine] " << message << '\n';
    });
    eniac_os::Monitor monitor(machine, std::cin, std::cout);
    std::filesystem::path initial;
    if (argc > 1) initial = argv[1];
    return monitor.loop(initial);
}
