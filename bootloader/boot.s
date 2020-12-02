[bits 16]
[ORG 0x7c00]

section .text
    global start
jmp 0:start
align 16
start:
    cld                 ;clear direction bit
    cli                 ;disable interupts
    xor ax, ax          ;set registers to zero
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov [disk_id], dl

    mov bp, start       ;setup stack
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
    call enableSSE
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
    push si
    mov si, part_read
    call _biosPrint
    pop si
    ret

%include "lib/A20.s"
%include "lib/SSE.s"
%include "lib/longmode.s"

times 500 db 0

[bits 64]
kernel:
