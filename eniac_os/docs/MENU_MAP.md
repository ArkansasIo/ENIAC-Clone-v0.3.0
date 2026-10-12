# ENIAC Program OS — Menu Map

This document describes the operator-facing *menu and submenu* layout of the
ENIAC Program OS front end. The menu tree is a **documentation-first design
artifact**: it specifies what a screen-based (menu-driven) operator console
would look like, so that a future TUI, desktop, or web front end can reuse the
same structure and the same Machine API.

This is **not** an archival reproduction of the historical ENIAC console, and
it is not a claim that the 1940s ENIAC ran a menu-driven operating system. It is
a modern educational operator workflow layered over the simplified decimal
machine implemented in this subproject.

## Menu tree

```text
ENIAC Program OS
└── 1. Main Menu
    ├── 1. Machine Control
    │   ├── 1. Start / Resume
    │   ├── 2. Step One Instruction
    │   ├── 3. Run To Completion
    │   ├── 4. Pause
    │   ├── 5. Stop
    │   └── 6. Reset Machine
    ├── 2. Program
    │   ├── 1. Load Program (.epr)
    │   ├── 2. List Instructions
    │   ├── 3. Inspect Instruction
    │   └── 4. Unload Program
    ├── 3. Accumulators
    │   ├── 1. Show Bank (A0..A19)
    │   ├── 2. Inspect Single Accumulator
    │   ├── 3. Set Accumulator
    │   └── 4. Clear Accumulator
    ├── 4. Diagnostics
    │   ├── 1. Machine Status
    │   ├── 2. Event Trace
    │   ├── 3. Fault Detail
    │   └── 4. Self-Test
    ├── 5. Configuration
    │   ├── 1. Show Active Configuration
    │   ├── 2. Reload From config/default_machine.json
    │   └── 3. Execution Budget
    └── 6. Help / About
        ├── 1. Command Index
        ├── 2. Program Format Reference
        ├── 3. Fidelity Notes
        └── 4. About This Build
```

## Navigation model

| Input            | Action                                            |
|------------------|---------------------------------------------------|
| number + Enter   | select the numbered menu entry                    |
| `b` / `back`     | return to the parent menu                         |
| `h` / `help`     | open the Help / About menu                        |
| `?`              | print the current menu's key legend               |
| `q` / `quit`     | leave the current menu; at the Main Menu, exit    |

Menus are numbered so they map cleanly onto the line-oriented monitor: each
menu entry corresponds to an underlying monitor command or a small sequence of
them. A front end may render the same tree as text, as a full-screen terminal
UI, or as a desktop/web panel.

## Design principles

- **One owner per action.** Each menu entry performs exactly one machine
  operation; there are no hidden multi-step effects.
- **State before action.** Machine Control always shows the current state
  (Ready, Running, Halted, Faulted) before offering a transition.
- **Destructive actions confirm.** Reset, Unload, and Clear Accumulator ask for
  confirmation before changing state.
- **No silent errors.** Malformed program input is rejected with a source line
  number, never partially applied.
- **No host side effects.** The simulator never touches the host filesystem
  beyond reading a program the operator explicitly names.

## Relationship to the line monitor

The currently implemented monitor (`src/monitor.cpp`) exposes the flat command
set `help, load, list, step, run, regs, status, reset, quit`. The menu tree
above is a superset organized for screen navigation. The mapping is:

| Menu entry                | Monitor command(s)          |
|---------------------------|-----------------------------|
| Machine Control → Step    | `step`                      |
| Machine Control → Run     | `run`                       |
| Machine Control → Reset   | `reset`                     |
| Program → Load            | `load PATH`                 |
| Program → List            | `list`                      |
| Accumulators → Show Bank  | `regs`                      |
| Diagnostics → Status      | `status`                    |
| Help → Command Index      | `help`                      |
| Main Menu → Exit          | `quit`                      |

Entries with no monitor command yet (Start/Pause/Stop, single-accumulator
inspection, event trace, self-test, configuration reload) are marked as
**planned** in their respective documents.

## Related documents

- [MENU_MAIN.md](MENU_MAIN.md) — top-level menu.
- [MENU_MACHINE_CONTROL.md](MENU_MACHINE_CONTROL.md) — execution and state.
- [MENU_PROGRAM.md](MENU_PROGRAM.md) — load, list, inspect, unload.
- [MENU_ACCUMULATORS.md](MENU_ACCUMULATORS.md) — the 20-register bank.
- [MENU_DIAGNOSTICS.md](MENU_DIAGNOSTICS.md) — status, events, faults, self-test.
- [MENU_CONFIGURATION.md](MENU_CONFIGURATION.md) — configuration and budget.
- [MENU_HELP.md](MENU_HELP.md) — help, format reference, fidelity notes, about.
- [MENU_SCREENS.md](MENU_SCREENS.md) — rendered mockups of every screen.
- [OPERATOR_UI.md](OPERATOR_UI.md) — presentation model and prompt.
- [OPERATOR_MANUAL.md](OPERATOR_MANUAL.md) — command reference and session.
