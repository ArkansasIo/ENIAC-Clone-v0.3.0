#pragma once
#include "eniac_os/machine.hpp"
#include <filesystem>
#include <iosfwd>
#include <string>

namespace eniac_os {
class Monitor {
public:
    Monitor(Machine& machine, std::istream& input, std::ostream& output);
    int loop(const std::filesystem::path& initial_program = {});
private:
    bool execute_line(const std::string& line);
    void print_help() const;
    Machine& machine_;
    std::istream& input_;
    std::ostream& output_;
};
} // namespace eniac_os
