# Roadmap

## Current baseline
- Standalone C++23 project.
- 20-register accumulator bank.
- Decimal-integer arithmetic with overflow and divide-by-zero checks.
- Text program parser and ten-opcode instruction set.
- Operator monitor and execution step budget.
- Unit tests and sample programs.

## Next milestones
1. Add named labels and assembler-style jump targets.
2. Add an interactive program editor and saved job queue.
3. Add function-table and wiring abstractions linked to the parent simulator.
4. Add event-log export and deterministic replay.
5. Add machine configuration parsing from config/default_machine.json.
6. Add GUI operator panel as a separate optional frontend.
7. Add historically sourced pulse and component models behind a separate fidelity layer.
8. Add fuzz tests for malformed programs and property tests for arithmetic.
