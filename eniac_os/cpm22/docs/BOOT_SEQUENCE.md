# Startup and boot sequence

This prototype starts as a host executable; it does not boot from a CP/M disk image or emulate a ROM/boot sector.

1. The host process constructs the virtual disk rooted at the optional command-line path (default `disk`).
2. The disk layer initializes drive directories A–D and user area 00.
3. The BDOS-like facade exposes disk operations to the shell.
4. The BIOS-like console adapter connects line input and text output to the host terminal.
5. The CCP-like shell prints its banner and enters the prompt loop.
6. `RUN filename.EPR` reads a file through the disk service, parses it with the ENIAC program parser, loads the simulated machine, and runs it with the simulator's execution-step bound.

This is an application startup sequence, not a recreation of CP/M's cold-start loader, BIOS jump table, BDOS image, CCP image, or ENIAC hardware startup.
