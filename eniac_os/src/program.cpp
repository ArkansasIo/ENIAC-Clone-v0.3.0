#include "eniac_os/program.hpp"
#include <charconv>
#include <fstream>
#include <sstream>
#include <string_view>

namespace eniac_os {
std::string opcode_name(OpCode op) {
    switch (op) {
        case OpCode::Load: return "LOAD";
        case OpCode::Add: return "ADD";
        case OpCode::Sub: return "SUB";
        case OpCode::Mul: return "MUL";
        case OpCode::Div: return "DIV";
        case OpCode::Store: return "STORE";
        case OpCode::Print: return "PRINT";
        case OpCode::Jump: return "JUMP";
        case OpCode::JumpIfNonZero: return "JNZ";
        case OpCode::Halt: return "HALT";
    }
    return "UNKNOWN";
}
ParseResult parse_program(std::istream& input, std::string name) {
    ParseResult result;
    result.program.name = std::move(name);
    std::string line;
    std::size_t line_number = 0;
    while (std::getline(input, line)) {
        ++line_number;
        const auto comment = line.find_first_of("#;");
        if (comment != std::string::npos) line.erase(comment);
        std::istringstream row(line);
        std::string op;
        if (!(row >> op)) continue;
        for (char& c : op) {
            if (c >= 'a' && c <= 'z') c = static_cast<char>(c - 'a' + 'A');
        }
        std::int64_t operand = 0;
        const bool no_operand = (op == "PRINT" || op == "HALT");
        if (!no_operand) {
            std::string token;
            if (!(row >> token)) {
                result.errors.push_back({line_number, "missing integer operand"});
                continue;
            }
            const auto parsed = std::from_chars(token.data(), token.data() + token.size(), operand);
            if (parsed.ec != std::errc{} || parsed.ptr != token.data() + token.size()) {
                result.errors.push_back({line_number, "operand must be a signed 64-bit integer"});
                continue;
            }
        }
        std::string extra;
        if (row >> extra) {
            result.errors.push_back({line_number, "unexpected trailing token: " + extra});
            continue;
        }
        OpCode code;
        if (op == "LOAD") code = OpCode::Load;
        else if (op == "ADD") code = OpCode::Add;
        else if (op == "SUB") code = OpCode::Sub;
        else if (op == "MUL") code = OpCode::Mul;
        else if (op == "DIV") code = OpCode::Div;
        else if (op == "STORE") code = OpCode::Store;
        else if (op == "PRINT") code = OpCode::Print;
        else if (op == "JUMP") code = OpCode::Jump;
        else if (op == "JNZ") code = OpCode::JumpIfNonZero;
        else if (op == "HALT") code = OpCode::Halt;
        else {
            result.errors.push_back({line_number, "unknown opcode: " + op});
            continue;
        }
        if (no_operand) operand = 0;
        if (code == OpCode::Store && (operand < 0 || operand >= 20)) {
            result.errors.push_back({line_number, "STORE destination must be 0..19"});
            continue;
        }
        if ((code == OpCode::Jump || code == OpCode::JumpIfNonZero) && operand < 0) {
            result.errors.push_back({line_number, "jump target must be a non-negative instruction index"});
            continue;
        }
        result.program.instructions.push_back({code, operand, line_number, line});
    }
    return result;
}
ParseResult load_program(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        ParseResult result;
        result.program.name = path.string();
        result.errors.push_back({0, "could not open program file"});
        return result;
    }
    return parse_program(file, path.string());
}
} // namespace eniac_os
