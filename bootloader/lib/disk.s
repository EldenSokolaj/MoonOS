_readDisk:
    pusha
    mov [0x7E00], byte 0    ;init start of new sector to 0
    mov ah, 2               ;read sectors from drive
    mov ch, 0               ;starting at head and cilinder 0
    mov dh, 0
    mov al, 10              ;read 5 segments
    mov cl, 2               ;starting at segment 2

    xor bx, bx
    mov es, bx
    mov bx, (0x7c00 + 512)  ;save segment 2 after the boot segment

    int 0x13

    jnc .done
    mov si, disk_error
    call _biosPrint
    jmp $

    .done:
        cmp [0x7E00], byte 0
        jne .exit
        mov si, disk_read_error
        call _biosPrint
        jmp $

    .exit:
        popa
        ret

    disk_error: strl("[FATAL ERROR] Invalid AND/OR Incorrect Disk ID")
    disk_read_error: strl("[FATAL ERROR] Failed to Load Second Sector From Disk")
