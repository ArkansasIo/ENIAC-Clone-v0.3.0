# Architecture

The project is organized as a small C++23 library plus a command-line front end and tests.

- `core`: machine lifecycle, configuration, clock and accumulator storage.
- `arithmetic`: decimal arithmetic abstraction.
- `control`: explicit operation programs and execution coordination.
- `config`: function-table constants and logical wiring.
- `io`: console reporting and event log.
- `diagnostics`: invariant checks and machine diagnostics.

The layers are deliberately separated so new simulation capabilities can be added without coupling the UI to machine state. Software operations provide an educational model and are not a historical claim about ENIAC's internal programming mechanism.

## FLOPPY 5.2 architecture
See [FLOPPY52_ARCHITECTURE.md](FLOPPY52_ARCHITECTURE.md) for the FLOPPY 5.2 disk-development-kit layers.
