# Memory and disk editor

The environment has 64 KiB of RAM (addresses 0000–FFFF) and a separate CP/M-style virtual disk. RAM is volatile until explicitly saved. Binary memory files preserve all byte values, including NUL and FF.

## Shell commands
- `MEM [address] [rows]`: spreadsheet-like address/byte/ASCII table.
- `MPEEK address`: inspect one byte.
- `MPOKE address value`: edit a byte (decimal or 0x-prefixed hex).
- `MFILL address count value`: fill a memory range.
- `MSAVE file address count`: save RAM range as binary.
- `MLOAD file address`: load a binary file at an address.
- `MREAD file address count`: read the requested prefix of a file into RAM.
- `MWRITE address count file`: write RAM range to disk.
- `MEXPORT file address count`: export table as CSV.
- `MIMPORT file`: import CSV byte cells into RAM using addresses from the CSV.
- `MEDIT [address]`: enter interactive cell editor. Inside it, `LOAD file address`, `READ file address count`, `SAVE file address count`, `WRITE address count file`, `CSVOUT file address count`, and `CSVIN file` are also available.
- `OPTIONS`: configure display options.

## Interactive editor
Commands: `SHOW [address] [rows]`, `CELL address byte` (alias `SET`), `FILL address count byte`, `OPTIONS`, `HELP`, `EXIT`. The table shows a hexadecimal address, byte cells in hex, and an optional ASCII column. Cell edits take effect immediately in RAM.

## Options
Inside OPTIONS: `ROWS 8|16`, `ASCII ON|OFF`, `COLOR OFF|GREEN|AMBER|WHITE|BLUE|CYAN`, `HEADER ON|OFF`, `SAVE`, `EXIT`. Saved options persist in `<disk-root>/settings/memory.ini`. ANSI colors require a compatible terminal.

## CSV spreadsheet interchange
CSV uses an address column, byte columns `b0` through `b7` or `b15`, and a display-only ASCII column. Edit the CSV in Excel or LibreOffice Calc, then import it with MIMPORT. This is spreadsheet interchange, not a MySQL database. The import writes byte cells to their explicit row addresses.
