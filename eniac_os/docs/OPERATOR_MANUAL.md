# Operator Manual

Start the monitor:
    ./build/eniac_os

Load a program on startup:
    ./build/eniac_os examples/addition.epr

## Commands
- help: list commands
- load PATH: load a program from a file
- list: show instruction indices and source lines
- step: execute one instruction
- run: execute until halt, fault, or step budget
- regs: print all 20 accumulators
- status: show program name, PC, and state
- reset: zero registers and reset PC
- quit: leave the monitor

## Typical session
    load examples/addition.epr
    list
    step
    regs
    run
    status
    quit

A loaded program is reset to PC zero and all accumulators are cleared. Run does not prompt before executing; use step for inspection.
