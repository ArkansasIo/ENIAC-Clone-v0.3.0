; FLOPPY 5.2 minimal BIOS boot-sector demonstration.
; Assemble with NASM: nasm -f bin boot/boot_sector.asm -o build/boot_sector.bin
; This demo prints a message and halts. It does NOT load a kernel.
BITS 16
ORG 0x7C00
start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00
    sti
    mov si, boot_message
.print:
    lodsb
    test al, al
    jz .halt
    mov ah, 0x0E
    mov bh, 0x00
    int 0x10
    jmp .print
.halt:
    cli
.loop:
    hlt
    jmp .loop
boot_message db 13, 10, 'FLOPPY 5.2 BOOT DEMO', 13, 10
             db 'BIOS boot sector loaded.', 13, 10
             db 'Kernel loader: not installed yet.', 13, 10, 0
times 510-($-$$) db 0
dw 0xAA55
