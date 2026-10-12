# Command reference

Commands are case-insensitive. Files use CP/M-style uppercase 8.3 names; wildcard matching is available in DIR.

| Command | Behavior |
|---|---|
| `DIR [pattern]` | List files in the current drive/user area; default is `*.*`. |
| `TYPE file` | Print file contents as text. |
| `ERA file` | Delete one file. Wildcard deletion is intentionally not implemented. |
| `REN new=old` | Rename a file within the same drive. Destination must not exist. |
| `COPY source destination` | Copy a file; destination must not exist. |
| `USER n` | Select user area 0–15. |
| `A:` … `D:` | Select a virtual drive. |
| `RUN file.EPR` | Parse and execute an ENIAC program using the existing simulator. |
| `STAT` | Show file count and byte total for the current area. |
| `VER` | Print the environment version and compatibility disclaimer. |
| `ECHO text` | Print text. |
| `CLS` | Clear a terminal that supports ANSI escape sequences. |
| `HELP`, `?` | Show supported commands. |
| `EXIT`, `BYE`, `QUIT` | Leave the shell. |

## Intentional differences

This implementation does not load `.COM` binaries, run 8080 machine code, parse CP/M command-tail memory, or implement CP/M's original FCB-based BDOS function numbers. RUN is for the ENIAC simulator's `.EPR` instruction format only.
