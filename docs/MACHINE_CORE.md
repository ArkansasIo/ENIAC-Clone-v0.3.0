# Machine Core

## Components
- `Machine`: lifecycle state and coordination.
- `Accumulator`: signed decimal value and arithmetic status flags.
- `AccumulatorBank`: checked collection of 20 accumulator units.
- `MachineClock`: deterministic simulated cycle counter.
- `MachineConfig`: machine metadata and configurable bounds.
- `EventLog`: append-only in-memory trace for the current run.
- `Diagnostics`: consistency checks and diagnostic reporting.

## Boundaries
The core is a software architecture model. It does not simulate analog voltages, vacuum-tube failures, or historical pulse timing at this stage. These concerns belong in future, isolated simulation modules.
