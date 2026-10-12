; Reusable 16-bit BIOS teletype string routine; DS:SI points to zero-terminated text.
BITS 16
print_string:
.next:
    lodsb
    test al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp .next
.done:
    ret
