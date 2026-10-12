# Architecture

## Layer model

```text
User terminal
    |
    v
CCP (Ccp) -------- command parsing, prompts, DIR/TYPE/ERA/REN/COPY/RUN
    |
    v
BDOS facade (Bdos) - file, drive, and user-area services
    |
    v
Disk abstraction (Disk) - 8.3 names, drive roots, user areas, host filesystem
    |
    +------------------------------+
    | BIOS console adapter (BiosConsole) handles host text input/output
    |
    v
ENIAC Machine / Program parser - executes .EPR decimal-machine programs
```

## Virtual storage

The disk root is configurable as the first command-line argument (defaults to `disk`). The disk abstraction creates drive roots A–D and user area 00 at startup. Areas are represented as `<root>/<drive>/USER00` through `USER15`. Filenames are normalized to uppercase and validated as 8.3 names. User areas are isolated, and path separators are rejected before any filesystem path is constructed.

## Separation of concerns

- **CCP**: command-line syntax and user-facing output.
- **BDOS-like facade**: operations that commands request.
- **Disk**: validation, virtual drive/user state, file operations.
- **BIOS console**: only host terminal I/O.
- **Machine adapter**: uses the existing ENIAC program parser and execution engine for RUN.

This is a teaching architecture inspired by CP/M's CCP/BDOS/BIOS separation. Its classes and calls do not implement CP/M's 8080 register-level BDOS ABI, FCB structures, DMA buffer conventions, or boot image.
