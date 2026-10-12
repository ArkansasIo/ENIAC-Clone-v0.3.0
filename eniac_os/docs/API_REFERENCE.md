# API Reference

## AccumulatorBank
- reset(): set all 20 values to zero.
- valid_index(index): check the index range.
- get(index): return a register value; throws out_of_range for invalid index.
- set(index, value): assign a register value.
- add/subtract/multiply/divide(index, operand): checked integer arithmetic.
- describe(): format the bank as a register table.

## Program parser
- parse_program(stream, name): parse an instruction stream and return instructions plus source-line errors.
- load_program(path): open and parse a program file.
- opcode_name(op): render a mnemonic.

## Machine
- load(program): replace the loaded program and reset machine state.
- reset(): clear registers, program counter, events, and state.
- step(): execute one instruction.
- run(max_steps): execute with a finite instruction budget.
- status(): return current program name, PC, and state.
- events(): read execution messages.

## Monitor
- loop(initial_program): start the command prompt and optionally load a program.
- Supported commands: help, load, list, step, run, regs, status, reset, quit.

Errors are reported as parse errors or StepResult messages. The API intentionally throws for direct invalid AccumulatorBank operations, while Machine catches runtime instruction faults and transitions to Faulted.
