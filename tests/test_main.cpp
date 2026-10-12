#include <cstdlib>
#include <iostream>
#include "eniac/arithmetic/decimal_alu.hpp"
#include "eniac/config/function_table.hpp"
#include "eniac/config/wiring.hpp"
#include "eniac/control/execution_engine.hpp"
#include "eniac/control/program.hpp"
#include "eniac/core/machine.hpp"
#include "eniac/diagnostics/diagnostics.hpp"
namespace { int failures = 0; void check(bool ok, const char* message) { if (!ok) { std::cerr << "FAIL: " << message << '\n'; ++failures; } } }
int main() {
    eniac::DecimalALU alu;
    check(alu.add(125,375).value == 500, "ALU addition");
    check(alu.subtract(500,125).value == 375, "ALU subtraction");
    check(alu.multiply(12,12).value == 144, "ALU multiplication");
    eniac::Machine machine;
    check(machine.start(), "machine starts");
    check(machine.load_value(0,125), "load A0");
    check(machine.load_value(1,375), "load A1");
    check(machine.add(0,1), "machine addition");
    check(machine.accumulators().at(0)->value() == 500, "addition result");
    machine.tick(); check(machine.clock().cycles() == 1, "clock tick");
    check(machine.stop(), "machine stops");
    check(!machine.load_value(0,1), "cannot load while stopped");
    check(machine.reset(), "machine resets");
    check(machine.accumulators().at(0)->value() == 0, "reset clears values");
    eniac::Program p; p.append({eniac::OperationCode::LoadConstant,0,0,7}); p.append({eniac::OperationCode::LoadConstant,1,0,8}); p.append({eniac::OperationCode::Add,0,1,0});
    check(machine.start(), "machine restarts"); eniac::ExecutionEngine{}.execute(machine,p);
    check(machine.accumulators().at(0)->value() == 15, "program result");
    check(machine.clock().cycles() == 3, "program clock count");
    eniac::FunctionTable table; table.set("answer",42); check(table.get("answer").value_or(0)==42, "function table"); check(!table.get("missing"), "missing constant");
    eniac::Wiring wiring; check(wiring.connect("A0","A1"), "connect"); check(!wiring.connect("","A1"), "reject empty wire");
    check(eniac::Diagnostics{}.inspect(machine).empty(), "default diagnostics");
    if (failures) { std::cerr << failures << " test(s) failed\n"; return EXIT_FAILURE; }
    std::cout << "All ENIAC-Clone tests passed\n"; return EXIT_SUCCESS;
}
