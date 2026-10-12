# Development Notes

- Use C++23 and keep APIs namespaced.
- Use explicit status/result types for recoverable failures.
- Validate disk geometry, lengths, and addresses at module boundaries.
- Keep hardware access separate from host-side tests.
- The in-process memory table is simulated; it does not access physical RAM.
- Raw disk images can overwrite data if written to a physical device. Test only in a disposable emulator or virtual machine.
