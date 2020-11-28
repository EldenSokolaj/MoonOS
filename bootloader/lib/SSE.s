; Enable SSE on the CPU
enableSSE:
    ; Load CPU feature flags into ecx and edx.
    mov eax, 1
    cpuid
    ; Check for FXSAVE/FXRSTOR support.
    test edx, (1 << 24)
    jz SSEerror
    ; Check for SSE1 support.
    test edx, (1 << 25)
    jz SSEerror
    ; Check for SSE2 support.
    test edx, (1 << 26)
    jz SSEerror
    ; Enable hardware FPU with monitoring.
    mov eax, cr0
    and eax, ~(1 << 2)   ; turn off CR0.EM bit (x87 FPU is present)
    or eax, (1 << 1)    ; turn on CR0.MP bit (monitor FPU)
    mov cr0, eax
    ; Make sure FXSAVE/FXRSTOR instructions save the contents of the FPU
    ; MMX, XMM and MXCSR registers. Enable the use of SSE instructions.
    ; And indicate that the kernel is capable of handling SIMD floating-
    ; point exceptions.
    mov eax, cr4
    or eax, (1 << 9) | (1 << 10)    ; CR4.OFXSR, CR4.OSXMMEXCPT
    mov cr4, eax
    ret

SSEerror:
    mov si, sse_error_text
    call _biosPrint
    jmp $

sse_error_text strl("SSE failed")
