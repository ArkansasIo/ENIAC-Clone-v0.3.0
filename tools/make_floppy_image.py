#!/usr/bin/env python3
"""Create a demo raw 1.44 MiB floppy image from a validated boot sector."""
import argparse
from pathlib import Path

IMAGE_SIZE = 1_474_560
SECTOR_SIZE = 512
SIGNATURE = bytes((0x55, 0xAA))

def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--boot", required=True, type=Path)
    parser.add_argument("--output", required=True, type=Path)
    args = parser.parse_args()
    boot = args.boot.read_bytes()
    if len(boot) != SECTOR_SIZE:
        parser.error(f"boot sector must be exactly {SECTOR_SIZE} bytes; got {len(boot)}")
    if boot[510:512] != SIGNATURE:
        parser.error("boot sector is missing the 0x55AA signature")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    image = bytearray(IMAGE_SIZE)
    image[:SECTOR_SIZE] = boot
    args.output.write_bytes(image)
    print(f"Wrote {args.output} ({len(image)} bytes, 2880 sectors)")
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
