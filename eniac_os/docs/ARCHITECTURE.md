# Architecture

## Subsystem boundaries
- Monitor: accepts operator commands and renders status.
- Program parser: reads line-oriented instructions and reports source line errors.
- Machine: owns program counter, execution state, event trace, and instruction dispatch.
- AccumulatorBank: owns 20 checked signed decimal registers.
- Instruction model: opcode, signed operand, source line, and original text.

## Execution path
Operator command -> Monitor -> Program parser or Machine -> instruction dispatch -> AccumulatorBank -> event/output callback.

## Machine state
- Ready: loaded or reset, ready to execute.
- Running: executing a step/run.
- Halted: HALT instruction or program end.
- Faulted: invalid jump, arithmetic fault, or execution step limit.

Reset clears registers, PC, events, and state, but leaves the currently loaded program available for rerun.

## Memory and safety model
This is a hosted C++ program, not bare-metal firmware. The standard library owns program text and event strings. Every register index is checked, arithmetic overflow is checked, division by zero is rejected, and run() has a step budget to stop accidental infinite loops.

## Fidelity boundary
The model uses a modern instruction sequence for accessibility. It does not simulate the historical ENIAC's electrical pulse timing, plugboard configuration, decimal ring counters, or physical function-table mechanisms at component level.
