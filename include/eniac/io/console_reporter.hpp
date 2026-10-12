#pragma once
#include <iosfwd>
namespace eniac {
class Machine;
class ConsoleReporter {
public:
    void report(const Machine& machine, std::ostream& out) const;
};
} // namespace eniac
