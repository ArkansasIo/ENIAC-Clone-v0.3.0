#pragma once
#include "eniac_os/instruction.hpp"
#include <filesystem>
#include <istream>
#include <string>

namespace eniac_os {
[[nodiscard]] ParseResult parse_program(std::istream& input, std::string name = "stdin");
[[nodiscard]] ParseResult load_program(const std::filesystem::path& path);
[[nodiscard]] std::string opcode_name(OpCode op);
} // namespace eniac_os
