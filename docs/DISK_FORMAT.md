# FLOPPY 5.2 Disk Format

The demo raw image is 1,474,560 bytes (1.44 MiB): 80 cylinders, 2 heads, 18 sectors per track, 512 bytes per sector, 2880 sectors total.

Sector 0 contains the 512-byte boot sector. This image writer does not create a FAT12 filesystem or directory entries. Boot signature bytes 55 AA are at offsets 510–511.
