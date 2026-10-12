# ENIAC Program OS (Educational Clone)

A standalone C++23 subproject that adds an operator console and program-control layer around a simplified ENIAC-inspired decimal machine. It is intentionally isolated under eniac_os/ and does not replace the existing ENIAC simulator.

This is a modern educational simulation, not a claim that the historical ENIAC used a conventional operating system. The software provides a monitor, a small program format, a bounded execution engine, accumulators, a step/run interface, and tests.

## Features
- Decimal accumulator bank with signed integer values.
- Small instruction set: LOAD, ADD, SUB, MUL, DIV, STORE, PRINT, JUMP, JNZ, HALT.
- Program parser for a simple line-oriented .epr format.
- Machine monitor commands: help, load, list, step, run, regs, reset, quit.
- Execution step limit and division-by-zero handling.
- Standalone CMake build and CTest tests.

## Build
From this directory:
    cmake -S . -B build
    cmake --build build
    ctest --test-dir build --output-on-failure
    ./build/eniac_os

Windows:
    cmake -S . -B build
    cmake --build build --config Release
    ctest --test-dir build -C Release --output-on-failure
    .\build\Release\eniac_os.exe

## Try the example
    ./build/eniac_os examples/addition.epr

The optional file argument loads the example, then opens the monitor. Use the run command to execute it.

## Scope
This project emulates a simplified decimal accumulator machine and a modern operator workflow. It does not reproduce ENIAC's full plugboard wiring, function tables, pulse timing, physical accumulators, or original programming procedures with electrical fidelity. See docs/HISTORICAL_SCOPE.md.
