# ENIAC-Clone v0.3.0

Modular C++23 educational simulator inspired by ENIAC, plus an isolated operator/program environment and a CP/M 2.2-inspired shell.

## Build main simulator
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## CP/M-style shell and memory editor
See [eniac_os/cpm22](eniac_os/cpm22/). This subproject has virtual drives, 8.3 files, a 64 KiB RAM table, binary save/load, CSV spreadsheet import/export, and persistent table options.

```sh
cmake -S eniac_os/cpm22 -B eniac_os/cpm22/build
cmake --build eniac_os/cpm22/build
ctest --test-dir eniac_os/cpm22/build --output-on-failure
./eniac_os/cpm22/build/eniac_cpm22
```

Memory editor guide: [MEMORY_EDITOR.md](eniac_os/cpm22/docs/MEMORY_EDITOR.md).

This is a CP/M-inspired educational shell, not binary-compatible CP/M 2.2. RUN executes ENIAC .EPR programs, not native CP/M .COM binaries.
