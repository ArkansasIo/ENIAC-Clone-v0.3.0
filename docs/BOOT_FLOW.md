# Boot and Loading Screen

BIOS loads the first sector at physical address 0x7C00 and transfers control. The demo initializes segment registers and stack, prints a short message with BIOS interrupt 10h, and halts.

The current boot sector does not load a second-stage loader or kernel. Future work: validate the boot drive, read sectors with BIOS interrupt 13h, check errors and retry safely, and transfer control to a documented load address.
