_testA20:
    push bx                 ;preserve bx
    push es
    mov bx, 0xFFFF          ;set es to 0x7E0E
    mov es, bx
    mov bx, 0x7E0E          ;pointer to magic number
    mov si, [es:bx]         ;will be 0xaa55 if A20 is disables, else garbage data
    pop es
    pop bx
    ret

_A20:
    pusha                   ;preserve registers
    mov ax, [0x7c00 + 510]  ;should be 0xaa55
    call _testA20
    cmp ax, si
    jne .end
    mov si, A20_B
    call _biosPrint
    call _enableA20
    call _testA20
    cmp ax, si
    jne .end
    mov si, A20_Fail
    call _biosPrint
    jmp $
    .end:
        mov si, A20_A
        call _biosPrint
        popa                ;restore registers and return
        ret

A20_B: strl("A20 line is disabled")

_enableA20:
    mov ax, 0x2401          ;use BIOS interrupt to enable A20 line
    int 0x15                ;NOTE: this will probably work, but if it doesn't,
    ret                     ;there ARE other possible ways that should work
