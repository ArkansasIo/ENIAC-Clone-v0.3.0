# Main Menu

The Main Menu is the root of the ENIAC Program OS operator console. Every
session starts here after the banner.

## Layout

```text
ENIAC Program OS 0.1 — educational monitor
Machine: Ready   Program: untitled (0 instructions)   PC: 0

1) Machine Control    start, step, run, pause, stop, reset
2) Program            load, list, inspect, unload
3) Accumulators       inspect the A0..A19 bank
4) Diagnostics        status, event trace, faults, self-test
5) Configuration      active config and execution budget
6) Help / About       commands, format, fidelity, build info
Q) Exit
```

## Entries

| # | Entry             | Opens                    | Purpose                                        |
|---|-------------------|--------------------------|------------------------------------------------|
| 1 | Machine Control   | MENU_MACHINE_CONTROL.md  | Drive execution and machine state transitions. |
| 2 | Program           | MENU_PROGRAM.md          | Manage the loaded `.epr` program.              |
| 3 | Accumulators      | MENU_ACCUMULATORS.md     | Inspect and edit the 20 decimal registers.     |
| 4 | Diagnostics       | MENU_DIAGNOSTICS.md      | Status, event trace, fault detail, self-test.  |
| 5 | Configuration     | MENU_CONFIGURATION.md    | Show/reload configuration and set the budget.  |
| 6 | Help / About      | MENU_HELP.md             | Reference material and build information.      |
| Q | Exit              | —                        | Leave the monitor; equivalent to `quit`.       |

## Status line

The status line is always visible and mirrors the machine's own status report:

- **Machine** — one of `Ready`, `Running`, `Halted`, `Faulted`.
- **Program** — program name and instruction count, or `untitled (0 instructions)`.
- **PC** — the zero-based program counter.

This corresponds to the monitor's `status` command.

## Keys

- `1`..`6` — open the numbered submenu.
- `q` — exit the monitor.
- `?` — print the key legend.

## Behinds the scenes

Selecting an entry opens a submenu; it never executes a machine operation by
itself. This keeps the top level safe to explore while a program is loaded.
