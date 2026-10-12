# Storage safety

The virtual disk is a host directory tree. The Disk class rejects slash, backslash, and colon characters inside filenames, normalizes names to uppercase, and limits base/extension lengths to CP/M-style 8.3. Drive-qualified names are restricted to A: through D:. ERA accepts a single filename only; it never interprets wildcard deletion. COPY and REN refuse to overwrite an existing destination.

Do not treat the virtual disk as a security sandbox against malicious local users; the application runs with the host user's filesystem permissions. Run it with a dedicated working directory if isolation from unrelated files is important.
