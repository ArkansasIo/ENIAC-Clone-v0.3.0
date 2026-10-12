#pragma once
#include <iosfwd>
#include <string>

namespace cpm22 {
// Host console adapter standing in for the minimum BIOS console interface.
class BiosConsole {
public:
    BiosConsole(std::istream& input, std::ostream& output);
    [[nodiscard]] bool read_line(std::string& line);
    void write(const std::string& text);
    void newline();
    void clear_screen();
private:
    std::istream& input_;
    std::ostream& output_;
};
} // namespace cpm22
