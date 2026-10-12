#include "eniac_os/accumulator.hpp"
#include "eniac_os/machine.hpp"
#include "eniac_os/program.hpp"
#include <cassert>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

int main() {
    using namespace eniac_os;

    AccumulatorBank bank;
    bank.set(0, 12);
    bank.add(0, 8);
    assert(bank.get(0) == 20);
    bank.subtract(0, 5);
    assert(bank.get(0) == 15);
    bank.multiply(0, 3);
    assert(bank.get(0) == 45);
    bank.divide(0, 9);
    assert(bank.get(0) == 5);

    bool rejected_index = false;
    try { (void)bank.get(20); } catch (const std::out_of_range&) { rejected_index = true; }
    assert(rejected_index);

    bool rejected_division = false;
    try { bank.divide(0, 0); } catch (const std::domain_error&) { rejected_division = true; }
    assert(rejected_division);

    std::istringstream source("LOAD 7\nADD 5\nMUL 2\nSTORE 3\nPRINT\nHALT\n");
    auto parsed = parse_program(source, "test-program");
    assert(parsed.ok());
    assert(parsed.program.instructions.size() == 6);

    std::vector<std::string> output;
    Machine machine([&output](const std::string& line) { output.push_back(line); });
    machine.load(parsed.program);
    const auto run_result = machine.run();
    assert(run_result.ok);
    assert(run_result.halted);
    assert(machine.accumulators().get(0) == 24);
    assert(machine.accumulators().get(3) == 24);
    assert(machine.state() == MachineState::Halted);
    assert(!output.empty());

    std::istringstream bad_source("WAT 5\nLOAD nope\nSTORE 99\n");
    auto bad = parse_program(bad_source, "bad");
    assert(!bad.ok());
    assert(bad.errors.size() == 3);

    std::istringstream zero_source("LOAD 9\nDIV 0\nHALT\n");
    auto zero_program = parse_program(zero_source, "division-by-zero");
    assert(zero_program.ok());
    machine.load(zero_program.program);
    const auto fault = machine.run();
    assert(!fault.ok);
    assert(machine.state() == MachineState::Faulted);

    std::istringstream loop_source("LOAD 1\nJNZ 1\n");
    auto loop_program = parse_program(loop_source, "bounded-loop");
    assert(loop_program.ok());
    machine.load(loop_program.program);
    const auto limited = machine.run(20);
    assert(!limited.ok);
    assert(machine.state() == MachineState::Faulted);

    return 0;
}
