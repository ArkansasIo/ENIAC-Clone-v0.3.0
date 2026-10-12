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

## Build
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/eniac
```

Windows:
```powershell
cmake -S . -B build
cmake --build . --config Release
ctest --test-dir build -C Release --output-on-failure
.\\build\\Release\\eniac.exe
```

## Fidelity boundary
This is an educational architecture model, not a cycle-accurate electrical simulation. Its operation sequence is a modern software convenience. Historical ENIAC behavior should be implemented only where supported by reliable technical or archival references.
