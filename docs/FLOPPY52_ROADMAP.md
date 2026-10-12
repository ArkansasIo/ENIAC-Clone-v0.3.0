# FLOPPY 5.2 Roadmap

- [x] C++23 modular project scaffold
- [x] Module registry, nested descriptors, fixed-width types, simulated memory table
- [x] BIOS boot-sector demo and text loading-screen mockup
- [x] Configuration reader and CLI foundations
- [ ] Second-stage bootloader with disk reads and error handling
- [ ] FAT12 filesystem implementation and tests
- [ ] Interactive disk/sector editor and persistent file manager
- [ ] SDK statement parser and diagnostics
- [ ] Memory table import/export and editor UI
- [ ] QEMU/Bochs automated boot smoke test

Raw disk images should be tested only in a disposable emulator or VM. The memory table is simulated and never accesses physical memory.
