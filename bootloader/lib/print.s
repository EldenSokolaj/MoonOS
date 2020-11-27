%define str(in) db in, 0x0
%define strl(in) db in, 13, 0xA, 0h

_biosPrint:
    pusha
    mov ah, 0x0E
    .loop:
    or [si], byte 0
    jz .done
    mov al, [si]
    int 0x10
    inc si
    jmp .loop
    .done:
        popa
        ret
