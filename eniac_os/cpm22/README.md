# ENIAC CP/M 2.2-style Operating Environment

Standalone C++23 shell inspired by CP/M 2.2, connected to the ENIAC educational simulator. Includes a CCP-like shell, BDOS-like file service, BIOS-like console, virtual drives A:–D:, user areas 0–15, 64 KiB RAM, binary memory files, spreadsheet CSV interchange, and ENIAC .EPR execution.

This is an educational CP/M-inspired implementation, not Digital Research CP/M and not a historical ENIAC operating system.

## Build
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/eniac_cpm22
```

## Example session
```text
A> MEM 0x0200 8
A> MPOKE 0x0200 65
A> MPEEK 0x0200
A> MSAVE MEMORY.BIN 0x0200 256
A> MLOAD MEMORY.BIN 0x0200
A> MEXPORT MEMORY.CSV 0x0200 256
A> MEDIT 0x0200
A> EXIT
```

Table options persist at `<disk-root>/settings/memory.ini`. Use MEDIT for cell editing and MEXPORT/MIMPORT to work with CSV in Excel or LibreOffice. See docs/MEMORY_EDITOR.md.
