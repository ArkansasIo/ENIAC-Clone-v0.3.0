#!/usr/bin/env bash
set -euo pipefail
cmake -S . -B build
cmake --build build --parallel
ctest --test-dir build --output-on-failure
if command -v nasm >/dev/null 2>&1; then
  mkdir -p build
  nasm -f bin boot/boot_sector.asm -o build/boot_sector.bin
  python3 tools/make_floppy_image.py --boot build/boot_sector.bin --output build/floppy52.img
else
  echo "NASM not found; skipped boot sector and floppy image."
fi
