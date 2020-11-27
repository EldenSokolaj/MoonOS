_checkLongmode:
    pusha
    pushfd
    pop eax
    mov ecx, eax
    or eax, 1 << 21 ;maybe should be xor :)
    push eax
    popfd
    pushfd
    pop eax
    xor eax, ecx
    jnz .next
    .fails:
    mov si, longmode_fail
    call _biosPrint
    jmp $
    .next:
        mov eax, 0x80000000
        cpuid
        cmp eax, 0x80000001
        jb .fails
        mov eax, 0x80000001
        cpuid
        test edx, 1 << 29
        jz .fails
    .done:
        mov si, longmode_det
        call _biosPrint
        popa
        ret

SwitchToLongMode:
; build the necessary tables
   xor bx,bx
   mov es,bx
   cld
   mov di,0xa000
    
   mov ax,0xb00f
   stosw
   
   xor ax,ax
   mov cx,0x07ff
   rep stosw
    
   mov ax,0xc00f
   stosw
    
   xor ax,ax
   mov cx,0x07ff
   rep stosw
    
   mov ax,0x018f
   stosw
    
   xor ax,ax
   mov cx,0x07ff
   rep stosw
    
    
   ;Enter long mode
    
   mov eax,10100000b				;Set PAE and PGE
   mov cr4,eax
    
   mov edx, 0x0000a000				;Point CR3 at PML4
   mov cr3,edx
    
   mov ecx,0xC0000080				;Specify EFER MSR
    
   rdmsr						;Enable Long Mode
   or eax,0x00000100
   wrmsr
    
   mov ebx,cr0					;Activate long mode
   or ebx,0x80000001				;by enabling paging and protection simultaneously
   mov cr0,ebx					;skipping protected mode entirely
    
   lgdt [gdt.pointer]				;load 80-bit gdt.pointer below
    
   jmp gdt.code:startLongMode			;Load CS with 64 bit segment and flush the instruction cache
    
    
    
   ;Global Descriptor Table
   gdt:
   dq 0x0000000000000000				;Null Descriptor
    
   .code equ $ - gdt
   dq 0x0020980000000000                   
    
   .data equ $ - gdt
   dq 0x0000900000000000                   
    
   .pointer:
   dw $-gdt-1					;16-bit Size (Limit)
   dq gdt						;64-bit Base Address
                           ;Changed from "dd gdt"
                           ;Ref: Intel System Programming Manual V1 - 2.1.1.1
    
    
   [BITS 64]
   startLongMode:
    cli						;Interupts are disabled because no IDT has been set up
    jmp 0x8000
