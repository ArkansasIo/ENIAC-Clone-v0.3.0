# Test plan
Automated tests cover 8.3 filename safety, disk file lifecycle, user isolation, drive selection, RAM reads/writes, fills, snapshots/restores, range bounds, and binary file roundtrips.
Manual smoke test: build, run MEM 0x0200 4, MPOKE 0x0200 65, MPEEK 0x0200, MSAVE TEST.BIN 0x0200 16, MFILL 0x0200 16 0, MLOAD TEST.BIN 0x0200, MEXPORT TABLE.CSV 0x0200 32, edit CSV in a spreadsheet, MIMPORT TABLE.CSV, then test MEDIT and OPTIONS persistence.
