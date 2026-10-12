#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace eniac_os {
enum class OpCode : std::uint8_t {
    Load, Add, Sub, Mul, Div, Store, Print, Jump, JumpIfNonZero, Halt
};

struct Instruction {
    OpCode op{OpCode::Halt};
    std::int64_t operand{0};
    std::size_t line{0};
    std::string source_text;
};

struct Program {
    std::string name{"untitled"};
    std::vector<Instruction> instructions;
};

struct ParseError {
    std::size_t line{0};
    std::string message;
};

struct ParseResult {
    Program program;
    std::vector<ParseError> errors;
    [[nodiscard]] bool ok() const noexcept { return errors.empty(); }
};
} // namespace eniac_os
