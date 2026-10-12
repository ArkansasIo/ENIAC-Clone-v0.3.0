#include <iostream>
#include "eniac/core/machine.hpp"
#include "eniac/io/console_reporter.hpp"
int main() {
    eniac::Machine machine;
    if (!machine.start()) { std::cerr << "Failed to start machine\n"; return 1; }
    (void)machine.load_value(0, 120);
    (void)machine.load_value(1, 30);
    (void)machine.add(0, 1);
    machine.tick();
    (void)machine.stop();
    eniac::ConsoleReporter{}.report(machine, std::cout);
    return 0;
}
