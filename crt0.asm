section .text

extern _init
extern main
extern exit

extern envc
extern envp

global _start
_start:
	mov ebp,0
	push ebp
	push ebp
	mov ebp,esp
	
	call init_stdlib

	push ecx
	push eax

	call _init

	call main

	push eax
	call exit

global init_stdlib
init_stdlib:
	mov [envc],ebx
	mov [envp],edx
	ret