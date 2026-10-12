#include "eniac/io/console_reporter.hpp"
#include <ostream>
#include "eniac/core/machine.hpp"
namespace eniac {
void ConsoleReporter::report(const Machine& machine, std::ostream& out) const {
    out << machine.config().name << '\n' << "State: " << to_string(machine.state()) << '\n' << "Cycles: " << machine.clock().cycles() << '\n' << "Accumulators:\n";
    for (std::size_t i = 0; i < AccumulatorBank::count; ++i) {
        const auto* a = machine.accumulators().at(i);
        out << "  A" << i << ": " << a->value() << " (overflow=" << (a->flags().overflow ? "yes" : "no") << ", negative=" << (a->flags().negative ? "yes" : "no") << ")\n";
    }
    out << "Events: " << machine.events().entries().size() << '\n';
}
} // namespace eniac
