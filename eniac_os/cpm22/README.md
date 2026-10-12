# ENIAC CP/M 2.2-style Operating Environment

A standalone C++23 command environment inspired by the workflow and command interpreter of CP/M 2.2, adapted to the existing ENIAC educational simulator. It provides a CCP-like shell, BDOS-like file services, a BIOS-like console boundary, four virtual drives (A:–D:), 16 user areas, and execution of ENIAC `.EPR` programs.

> This is a modern educational implementation inspired by CP/M's architecture. It is not Digital Research CP/M, does not contain CP/M proprietary binaries, and is not an authentic historical ENIAC operating system.

## Build and test

From this directory:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/eniac_cpm22
```

Windows (Visual Studio generator):

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
.\build\Release\eniac_cpm22.exe
```

## First session

The shell creates its virtual disk directory on first launch. By default the disk root is `./disk` relative to the current working directory. The virtual filesystem maps drive and user area names to host directories; all CP/M-visible filenames are validated as 8.3 names.

```text
A> HELP
A> DIR
A> TYPE README.TXT
A> USER 1
A> A:
A> RUN HELLO.EPR
A> EXIT
```

Place example programs in `disk/A/USER00` before running them. The repository's `examples/` directory contains starter files.

## Implemented commands

- `DIR [pattern]`, `TYPE file`, `ERA file`, `REN new=old`, `COPY source destination`
- `USER 0..15`, `A:` through `D:`, `STAT`, `VER`, `HELP`, `CLS`, `ECHO text`
- `RUN program.EPR` loads and runs an ENIAC program through the existing machine simulator
- `EXIT` / `BYE`

This is a deliberately small CP/M-style command subset, not a claim of full CP/M 2.2 binary/API compatibility. See `docs/` for architecture, command semantics, and limitations.
