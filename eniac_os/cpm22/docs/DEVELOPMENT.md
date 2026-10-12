# Development guide

## Prerequisites
- CMake 3.20 or newer
- A C++23 compiler (recent GCC, Clang, or MSVC)
- Git (optional, for cloning)

## Build
Run `scripts/build.sh` on POSIX systems, or use the CMake commands in the README on Windows.

## Add a shell command
1. Add command behavior to `Ccp::execute_line` in `src/ccp.cpp`.
2. Use the BDOS facade for storage operations; avoid direct host filesystem calls in CCP code.
3. Add user-facing syntax to `Ccp::help` and `docs/COMMAND_REFERENCE.md`.
4. Add tests for success, malformed input, and failure cases.
5. Run CTest before committing.

## Add a BDOS service
Implement a narrow operation in `Bdos`, backed by `Disk`. Keep host path construction inside `Disk`, validate all filenames, and ensure tests use a temporary disk root.
