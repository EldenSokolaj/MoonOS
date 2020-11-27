[bits 64]

global start
extern kmain 	          ;kmain is defined in the c++ file
start:
  cli 			            ;block interrupts
  mov rsp, stack_space	;set stack pointers
  mov rbp, rsp
  call kmain
  hlt		 	              ;halt the CPU

section .bss
  resb 8192		          ;8KB for stack
  stack_space:
