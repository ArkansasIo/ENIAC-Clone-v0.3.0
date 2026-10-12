# Roadmap

## Implemented in 0.1
- CCP-like interactive command interpreter.
- BDOS-like file service facade and BIOS-like console adapter.
- Virtual drives A–D, user areas 0–15, safe 8.3 names.
- DIR, TYPE, ERA, REN, COPY, USER, drive switching, STAT, VER, ECHO, CLS, HELP, EXIT.
- RUN for ENIAC `.EPR` programs.
- CMake build and storage tests.

## Possible next milestones
- Add a CP/M-style line editor and transient command scripts.
- Add directory wildcards to ERA only after confirmation prompts and dedicated tests.
- Add disk usage/capacity reporting with a documented virtual allocation model.
- Add a debugger command for ENIAC program stepping and accumulator inspection.
- Add a text editor that saves through the BDOS facade.
- Add a binary disk-image format only with explicit geometry and serialization tests.
- Consider an 8080 emulator as a separate optional module before attempting .COM compatibility.
