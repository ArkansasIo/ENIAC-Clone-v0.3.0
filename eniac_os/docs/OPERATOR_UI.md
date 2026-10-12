# Operator UI Design

## Presentation model
The first frontend is a line-oriented terminal monitor. It is kept independent from the machine core so future terminal, desktop, or web frontends can reuse the same Machine API.

## Prompt
The prompt is eniac-os>. Output messages are prefixed by the machine callback in the executable.

## Command navigation
- help: command index.
- load PATH: replace current program and reset machine state.
- list: inspect zero-based instruction indices.
- step: advance one instruction.
- run: execute until halt, fault, or budget exhaustion.
- regs: display all 20 accumulator values.
- status: show current PC and state.
- reset: clear registers and execution trace, retain loaded program.
- quit: exit.

## UI principles
- Never silently accept malformed program input.
- Keep parse errors tied to source line numbers.
- Expose PC and machine state for repeatable debugging.
- Keep destructive filesystem or host-system actions out of the simulator.
- Future UI should show instruction listing, accumulator panel, event log, and program load/save panel.
