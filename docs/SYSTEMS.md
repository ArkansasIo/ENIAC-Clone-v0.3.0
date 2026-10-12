# Systems Reference

| System | Responsibility |
|---|---|
| Machine | Lifecycle and coordination |
| Accumulator | Signed decimal state and status flags |
| AccumulatorBank | Checked access to accumulator units |
| MachineClock | Deterministic software cycle count |
| DecimalALU | Decimal arithmetic operations |
| Program | Explicit operation sequence |
| ExecutionEngine | Validated program dispatch |
| MasterProgrammer | Repeat-count abstraction |
| FunctionTable | Stored constants for software operations |
| Wiring | Validated logical endpoint routes |
| EventLog | Runtime trace |
| Diagnostics | Invariant checking |
| ConsoleReporter | Text output for machine state |

The names describe this model's software components. They should not be interpreted as a claim that every software component maps one-to-one to an original physical ENIAC unit.
