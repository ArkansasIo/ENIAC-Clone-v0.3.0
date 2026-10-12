# EPR Program Format

One instruction per line. Blank lines are ignored. Lines beginning with # or ; are comments; inline comments are also accepted.

## Instructions
| Opcode | Operand | Behavior |
|---|---|---|
| LOAD | signed integer | Replace A0 with immediate value |
| ADD | signed integer | Add immediate value to A0 |
| SUB | signed integer | Subtract immediate value from A0 |
| MUL | signed integer | Multiply A0 by immediate value |
| DIV | signed integer | Divide A0 by immediate value using integer division |
| STORE | 0..19 | Copy A0 to the selected accumulator |
| PRINT | none | Emit A0 |
| JUMP | instruction index | Set PC to zero-based instruction index |
| JNZ | instruction index | Jump if A0 is nonzero |
| HALT | none | Stop execution |

Jump targets are zero-based indices in the parsed instruction list, not source line numbers. A jump outside the program faults at runtime. DIV 0 faults. Arithmetic is signed 64-bit integer arithmetic and overflow faults.

Example:
    LOAD 7
    ADD 5
    PRINT
    HALT
Expected output: A0 = 12
