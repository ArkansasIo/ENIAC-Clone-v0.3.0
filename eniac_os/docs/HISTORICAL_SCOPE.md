# Historical Scope and Fidelity Notes

The historical ENIAC was an electronic numerical integrator and computer programmed through physical configuration, including plugboards, switches, function tables, accumulators, and coordinated control. It did not run this modern command-line “operating system.”

This project uses the phrase “Program OS” for an educational software layer that manages program loading, execution, status, and an operator console around a simplified ENIAC-inspired machine model. It is a clone of a conceptual workflow, not a hardware-faithful replica or a claim about the original machine's software.

The current model is intentionally abstract:
- signed 64-bit integer values stand in for decimal accumulator state;
- instructions are textual software conveniences;
- jumps use zero-based instruction indices;
- timing is instruction-step based, not pulse/cycle accurate;
- physical wiring and component-level behavior are not yet simulated.

For historical accuracy, later work should be grounded in primary technical documentation, manuals, schematics, and reputable archival sources. New features should label which behavior is historically supported and which is a modern convenience.
