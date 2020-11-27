[bits 16]
[ORG 0x7c00]

section .text
    global _start

_start:
    cld                 ;clear direction bit
    cli                 ;disable interupts
    xor ax, ax          ;set registers to zero
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov [disk_id], dl

    mov bp, _start      ;setup stack
    mov sp, bp

    mov si, welcome     ;print welcome
    call _biosPrint
    call _readDisk      ;load second segment into memory (right after the boot segment)
    call _seg           ;mainly just to show that the second sector has been loaded into memory
    call _A20           ;test for A20 line, and if it is disabled enable it
    call _checkLongmode ;check if longmode is supported, results in fatal error if not
    push ax     ;switch to vga graphics mode
    mov ah, 0
    mov al, 0x13
    int 0x10
    pop ax      ;end vga graphics mode switch
    jmp SwitchToLongMode

%include "lib/print.s"
%include "lib/disk.s"

welcome: strl("Welcome to Moon OS")
switch: strl("Segment Load Sucessfull")
longmode_fail: strl("[FATAL ERROR] Could Not Detect Long Mode (x86_64)")
longmode_det: strl("Long Mode Detected")
A20_A: strl("A20 line is enabled")
A20_Fail: strl("[FATAL ERROR] A20 Line Not Found")
disk_cycle: db 0
disk_id: db 0
full_read: strl("20 Segments Read")
part_read: strl("# Segments Read")

times 510-($-$$) db 0
   db 0x55
   db 0xAA

_seg:
    pusha
    mov si, switch
    call _biosPrint

    mov ah, 2               ;read sectors from drive
    mov ch, 0               ;starting at head and cilinder 0
    mov dh, 0
    mov cl, 3               ;starting at segment 3

    xor bx, bx
    mov es, bx
    mov bx, 0x8000

    .loop:
        mov dl, [disk_id]
        mov al, 1           ;read one segment
        int 0x13            ;load
        jc .show_part_done  ;when we can read no more, stop
        inc byte [disk_cycle]       ;update disk_cycle var
        cmp [disk_cycle], byte 20   ;this will max out after reading 20 segments
        je .show_done               ;if we have loaded 20 segments without error, stop
        inc cl
        add bx, 513         ;next space in memory
        jmp .loop
    .show_done:
        mov si, full_read
        call _biosPrint
        jmp .done
    .show_part_done:
        mov si, part_read
        call _biosPrint
    .done:
        popa
        ret

%include "lib/A20.s"
%include "lib/longmode.s"

times 143 db 0

[bits 64]
kernel:
