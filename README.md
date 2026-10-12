# ENIAC-Clone v0.3.0

A modular C++23 educational simulator inspired by ENIAC, with an expanded machine-core layer.

## Machine-core systems
- `Machine`: lifecycle, execution state and coordination.
- `Accumulator`: signed decimal state and arithmetic flags.
- `AccumulatorBank`: checked access to the 20 accumulators.
- `MachineClock`: deterministic simulated cycle counter.
- `MachineConfig`: configurable limits and metadata.
- `DecimalALU`: decimal arithmetic abstraction.
- `Program` and `ExecutionEngine`: explicit, bounded operation sequences.
- `MasterProgrammer`: repeat-count control abstraction.
- `FunctionTable` and `Wiring`: constants and validated routes.
- `EventLog` and `Diagnostics`: trace and invariant checks.

## Build the main simulator
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/eniac
```

## Standalone ENIAC Program OS
The isolated [eniac_os/](eniac_os/) subproject provides an operator console, a small `.EPR` program format, and bounded execution.

```sh
cmake -S eniac_os -B eniac_os/build
cmake --build eniac_os/build
ctest --test-dir eniac_os/build --output-on-failure
./eniac_os/build/eniac_os eniac_os/examples/addition.epr
```

## CP/M 2.2-inspired command environment
[eniac_os/cpm22/](eniac_os/cpm22/) adds a separate C++23 shell inspired by the CCP/BDOS/BIOS architecture of CP/M 2.2, with virtual drives A:–D:, user areas 0–15, CP/M-style 8.3 filenames, file commands, and `RUN` support for ENIAC `.EPR` programs.

```sh
cmake -S eniac_os/cpm22 -B eniac_os/cpm22/build
cmake --build eniac_os/cpm22/build
ctest --test-dir eniac_os/cpm22/build --output-on-failure
./eniac_os/cpm22/build/eniac_cpm22
```

The CP/M-inspired shell is a modern educational environment, not Digital Research CP/M, not binary-compatible with CP/M 2.2, and not a historical operating system used by ENIAC. See each subproject's documentation for its scope and limitations.

## Fidelity boundary
This is an educational architecture model, not a cycle-accurate electrical simulation. Historical ENIAC behavior should be implemented only where supported by reliable technical or archival references.
