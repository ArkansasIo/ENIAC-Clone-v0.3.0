# ENIAC-Clone v0.3.0
Modular C++23 educational simulator inspired by ENIAC, plus an isolated operator/program environment and a CP/M 2.2-inspired shell.

> This repository also contains the **FLOPPY 5.2** modular disk development kit (see below).

## Build main simulator
Requires CMake 3.25+ and a C++23 compiler.

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

---

# FLOPPY 5.2 - Modular Disk Development Kit
FLOPPY 5.2 is a modular developer-tool and bootable floppy-image project scaffold. It contains C++23 host-side SDK foundations, a BIOS boot-sector demonstration, assembly examples, module/type registries, configuration, tests, and disk-image build utilities.

> This is a source scaffold, not a complete operating system. The BIOS demo prints a message and halts; it does not yet load a second-stage kernel. Build and test only in an emulator.

## Structure
- `boot/` - BIOS boot sector and assembly logic examples
- `include/floppy52/` - public C++ SDK headers and types
- `src/` - CLI, module registry, memory simulator, configuration reader
- `sdk/modules/` - sample module metadata and disk SDK types
- `config/` - default configuration and module manifest
- `tools/` - build scripts and raw floppy image builder
- `tests/` - C++ tests
- `docs/` - architecture, disk format, boot flow, roadmap
## Build host tools
Requires CMake 3.25+ and a C++23 compiler.

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Assemble a boot-sector demo
Requires NASM:

```sh
mkdir -p build
nasm -f bin boot/boot_sector.asm -o build/boot_sector.bin
python3 tools/make_floppy_image.py --boot build/boot_sector.bin --output build/floppy52.img
```

The result is a raw 1.44 MiB image containing only the boot sector and blank space, not a FAT12 filesystem. Use it in a disposable emulator/VM; never write it to a physical disk without understanding the consequences.

## CLI commands
`help`, `modules`, `memory`, `types`, `load-config <path>`, and `quit`.

The memory table is simulated in-process and does not access physical RAM.

## Roadmap
See [docs/FLOPPY52_ROADMAP.md](docs/FLOPPY52_ROADMAP.md) and [docs/FLOPPY52_ARCHITECTURE.md](docs/FLOPPY52_ARCHITECTURE.md).
