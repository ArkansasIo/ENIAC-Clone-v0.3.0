# Command reference
Commands are case-insensitive. Disk filenames use uppercase CP/M-style 8.3 names. Addresses/counts accept decimal or 0x-prefixed hex.

| Command | Behavior |
|---|---|
| DIR [pattern], TYPE file | List or display files |
| ERA file, REN new=old, COPY src dst | File operations |
| USER n, A:–D: | Select user area or drive |
| RUN file.EPR | Execute ENIAC simulator program |
| MEM [address] [rows] | View 64 KiB memory table |
| MPEEK address | Read byte |
| MPOKE address value | Write byte |
| MFILL address count value | Fill RAM range |
| MSAVE file address count | Save RAM range as binary |
| MLOAD file address | Load binary file to RAM |
| MREAD file address count | Read file prefix into RAM |
| MWRITE address count file | Save RAM range to disk |
| MEXPORT file address count | Export CSV table |
| MIMPORT file | Import CSV byte cells |
| MEDIT [address] | Interactive memory editor |
| OPTIONS | Table display settings |
| STAT, VER, ECHO, CLS, HELP, EXIT | General shell commands |

MEDIT commands: SHOW [address] [rows], CELL address byte, FILL address count byte, OPTIONS, HELP, EXIT.
