#include "cpm22/bios.hpp"
#include <iostream>
#include <istream>
#include <ostream>
namespace cpm22 {
BiosConsole::BiosConsole(std::istream& input, std::ostream& output) : input_(input), output_(output) {}
bool BiosConsole::read_line(std::string& line) { return static_cast<bool>(std::getline(input_, line)); }
void BiosConsole::write(const std::string& text) { output_ << text; output_.flush(); }
void BiosConsole::newline() { output_ << '\n'; output_.flush(); }
void BiosConsole::clear_screen() { output_ << "\x1B[2J\x1B[H"; output_.flush(); }
} // namespace cpm22
