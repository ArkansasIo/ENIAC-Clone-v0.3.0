# Test plan

Automated tests cover:
- Lowercase to uppercase filename normalization.
- Rejection of traversal separators and overlong 8.3 names.
- Write/read round trip.
- Copy and rename without destination overwrite.
- User-area isolation.
- File deletion.
- Drive selection.

Manual smoke test:
1. Build and launch the shell with a temporary disk root.
2. Run HELP, VER, DIR, USER 1, A:, STAT, and EXIT.
3. Place HELLO.EPR in A/USER00, then run TYPE HELLO.EPR and RUN HELLO.EPR.
4. Test malformed filenames and absent files; confirm the shell stays usable.
