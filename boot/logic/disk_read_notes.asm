; Disk-read design note for a future second stage (not linked to demo).
; BIOS INT 13h CHS read: AH=02h, AL=count, CH=cylinder, CL=sector (1-based),
; DH=head, DL=drive, ES:BX=destination. Check carry flag and retry on errors.
; A production loader must validate geometry, image bounds, retries, and destination.
BITS 16
disk_read_placeholder:
    clc
    ret
