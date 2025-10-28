section .text

extern _init
extern main
extern exit

extern envc
extern envp

extern _late_init_stdlib

global _start
_start:
	mov ebp,0
	push ebp
	push ebp
	mov ebp,esp
	
	call _early_init_stdlib

	push ecx
	push eax

	call _init
	
	call _late_init_stdlib

	call main

	push eax
	call exit

global _early_init_stdlib
_early_init_stdlib:
	mov [envc],ebx
	mov [envp],edx
	ret