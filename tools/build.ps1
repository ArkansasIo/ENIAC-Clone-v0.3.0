$ErrorActionPreference = "Stop"
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
if (Get-Command nasm -ErrorAction SilentlyContinue) {
    New-Item -ItemType Directory -Force -Path build | Out-Null
    nasm -f bin boot/boot_sector.asm -o build/boot_sector.bin
    python tools/make_floppy_image.py --boot build/boot_sector.bin --output build/floppy52.img
} else {
    Write-Host "NASM not found; skipped boot sector and floppy image."
}
