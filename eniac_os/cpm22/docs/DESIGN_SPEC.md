# Design specification

## Goals

1. Offer a CP/M 2.2-inspired interactive operator environment around the ENIAC educational machine.
2. Keep the CCP, BDOS-like services, BIOS console, and storage backend independently testable.
3. Use safe host-file operations with a deliberately constrained CP/M-like namespace.
4. Run the existing ENIAC `.EPR` programs from the shell.
5. Keep this implementation standalone and buildable with CMake/C++23.

## Functional requirements

- Drives A: through D: and user areas 0 through 15.
- Uppercase normalization and strict 8.3 filename validation.
- File listing, reading, writing service, deleting, renaming, and copying.
- Interactive shell with clear error messages.
- Run valid ENIAC programs and report parse/execution errors.
- Unit tests for filename validation, user isolation, and file lifecycle.

## Non-goals

- CP/M binary or source-code compatibility.
- 8080/Z80 CPU emulation or .COM execution.
- Exact disk geometry, directory entries, allocation vectors, DPB/DPH, FCBs, DMA buffers, or CP/M boot sector.
- An authentic historical ENIAC operating system or cycle-accurate ENIAC electrical model.

## Safety and data integrity

The virtual disk is a directory tree. All user-controlled filenames are validated before path composition. Rename and copy refuse to overwrite existing destinations. ERA only accepts one normalized filename, not wildcard patterns. The selected user area is separate for each drive.
