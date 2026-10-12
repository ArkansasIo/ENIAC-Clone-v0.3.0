# ENIAC Program OS Design Specification

## Product definition
A small hosted program-control environment for a decimal-accumulator computer model. The term OS refers to the monitor, loader, execution control, status reporting, and job/program format—not to a historically documented ENIAC operating system.

## Requirements
- R1: parse a bounded line-oriented program file.
- R2: provide 20 checked accumulator registers.
- R3: support immediate arithmetic and control-flow instructions.
- R4: provide an interactive monitor for loading, inspecting, stepping, running, and resetting programs.
- R5: reject invalid opcodes, operands, accumulator indices, arithmetic overflow, divide-by-zero, and invalid jumps.
- R6: bound execution steps.
- R7: build independently with CMake and C++23.
- R8: test parser and machine behavior with CTest.

## Data contracts
Instruction contains opcode, signed integer operand, source line, and original source text. Program contains a name and ordered instruction vector. PC is a zero-based instruction index. A0 is the arithmetic working accumulator. STORE n copies A0 into accumulator n.

## Error policy
Parser errors prevent a program from loading. Runtime errors transition Machine to Faulted. A faulted machine must be reset or reloaded before execution continues. The run step limit prevents accidental infinite loops.

## Extension points
The parser and instruction model are deliberately separated from Machine dispatch. Future versions may add labels, indirect accumulator operands, function tables, wiring maps, decimal digit constraints, persistent jobs, and alternate frontends without changing the monitor contract.
