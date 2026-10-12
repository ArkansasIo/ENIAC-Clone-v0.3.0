# Machine Control Menu

Drives execution and machine-state transitions. Every entry reflects one
operation on the `Machine` class and requires the machine to be in a state that
permits it.

## Layout

```text
Machine Control
State: Ready   PC: 0   Program: addition.epr (4 instructions)

1) Start / Resume      begin execution from the current PC
2) Step One            execute exactly one instruction
3) Run To Completion   execute until HALT, fault, or budget
4) Pause               suspend a running program (planned)
5) Stop                end execution and hold state (planned)
6) Reset Machine       clear registers, PC, and event trace
B) Back
```

## Entries

| # | Entry             | Allowed states          | Effect                                                        | Monitor |
|---|-------------------|-------------------------|---------------------------------------------------------------|---------|
| 1 | Start / Resume    | Ready, Halted, Faulted¹ | Transition to Running and continue from PC.                   | planned |
| 2 | Step One          | Ready, Running          | Execute one instruction; update PC, registers, event trace.   | `step`  |
| 3 | Run To Completion | Ready, Running          | Execute until HALT, fault, or the step budget is exhausted.   | `run`   |
| 4 | Pause             | Running                 | Suspend execution, keep PC and state for a later resume.      | planned |
| 5 | Stop              | Running                 | Stop execution and return to Ready without clearing registers.| planned |
| 6 | Reset Machine     | any                     | Zero all accumulators, reset PC, clear events and state.      | `reset` |

¹ Resuming from Faulted is permitted only after the operator reviews the fault
in Diagnostics; the machine returns to Ready first.

## State transitions

```text
Ready ──start/step/run──▶ Running ──halt──▶ Halted
  ▲                          │                  │
  │                          ├──fault──▶ Faulted │
  │                          │                  │
  └──────────reset───────────┴──────────────────┘
        pause/stop (planned) return to Ready
```

- **Ready** — a program is loaded or the machine was just reset.
- **Running** — a step or run is in progress.
- **Halted** — a HALT instruction executed or the program ran off its end.
- **Faulted** — invalid jump target, arithmetic fault, divide-by-zero, or the
  execution step budget was exhausted.

## Confirmation rules

- **Reset Machine** asks for confirmation: `Reset machine? All accumulators
  and the event trace will be cleared. [y/N]`.
- **Stop** and **Pause** do not confirm; they are non-destructive.
- **Run To Completion** warns if the program has no HALT instruction, because it
  will otherwise end by faulting on the step budget.

## Notes

- A loaded program resets to PC 0 with all accumulators cleared, per the machine
  contract. Use **Step One** for inspection rather than **Run**.
- The run budget is configurable in the Configuration menu; see
  [MENU_CONFIGURATION.md](MENU_CONFIGURATION.md).
