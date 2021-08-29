#include <stdio.h>
#include <stdlib.h>

int envc;
char **envp;

char *getenv(const char *name) {
	for (uint32_t i = 0; i < envc; i+=2) {
		if (!strcmp(envp[i],name))
			return envp[i+1];
	}
	return 0;
}

void _late_init_stdlib() {
	_init_malloc();
}

uint32_t _syscall0(uint32_t syscall_num) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num):"memory");
	return retval;
}

uint32_t _syscall1(uint32_t syscall_num, uint32_t param1) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1):"memory");
	return retval;
}

uint32_t _syscall2(uint32_t syscall_num, uint32_t param1, uint32_t param2) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2):"memory");
	return retval;
}

uint32_t _syscall3(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2),"d"(param3):"memory");
	return retval;
}

uint32_t _syscall4(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2),"d"(param3),"S"(param4):"memory");
	return retval;
}

uint32_t _syscall5(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2),"d"(param3),"S"(param4),"D"(param5):"memory");
	return retval;
}

void writestring(char *string) {
	_syscall1(0,(uint32_t)(uintptr_t)string);
}

uint32_t exec(char *name) {
	return _syscall3(1,(uint32_t)(uintptr_t)name,0,0);
}

uint32_t exec_args(char *name, char **arguments, char **environment) {
	return _syscall3(1,(uint32_t)(uintptr_t)name,(uint32_t)(uintptr_t)arguments,(uint32_t)(uintptr_t)environment);
}

void exit(uint32_t code) {
	_syscall1(2,code);
	while(1);
}

void yield() {
	_syscall0(6);
}

uint32_t waitpid(uint32_t pid) {
	_syscall1(10,pid);
	return _syscall0(11);
}

uint32_t getpid() {
	return _syscall0(7);
}

uint32_t fork() {
	return _syscall0(25);
}

void *map_mem(void *address) {
	return (void *)(uintptr_t)_syscall1(26,(uint32_t)(uintptr_t)address);
}

uint64_t get_ticks() {
	uint64_t low;
	uint64_t high;
	low = _syscall1(24, false);
	high = _syscall1(24, true);
	return (high << 32) | low;
}
