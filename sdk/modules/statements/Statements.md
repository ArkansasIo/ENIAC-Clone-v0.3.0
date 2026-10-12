# FLOPPY 5.2 SDK statements

These statements are design-level syntax for a future parser, not arbitrary machine-code execution.

- `MODULE <id>` — declare a module identity.
- `SUBMODULE <id>` — declare a child module.
- `TYPE <name> = <primitive>` — declare a type alias.
- `ARRAY <name> : <type> [<count>]` — describe a fixed-size array.
- `READ <address>` — read from simulated memory.
- `WRITE <address> <byte>` — write to simulated memory.
- `LOAD CONFIG <path>` — load key/value configuration.
- `DISK INFO` — report disk geometry/capacity metadata.

The present CLI implements only its documented commands.
