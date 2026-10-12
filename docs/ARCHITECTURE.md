# Architecture

## Layers

1. Boot: 512-byte x86 BIOS boot-sector demo.
2. Loader: planned second stage to read sectors and load a kernel.
3. Core SDK: fixed-width primitives, status results, address ranges.
4. Module registry: module IDs, descriptors, child module lists.
5. Memory simulator: byte-addressed table for host-side tests; not physical RAM.
6. Developer tools: CLI, configuration reader, build scripts.
7. Disk tools: raw floppy-image writer for emulator experiments.

Keep hardware-specific operations behind interfaces so the SDK remains testable in an ordinary host process. Future extensions include FAT12, second-stage loader, disk editor, statement parser, memory import/export, and diagnostics.
