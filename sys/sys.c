#include <stdio.h>
#include <stdlib.h>

int envc;
char **envp;

char *getenv(char *name) {
	for (uint32_t i = 0; i < envc; i+=2) {
		if (!strcmp(envp[i],name))
			return envp[i+1];
	}
	return 0;
}

void _late_init_stdlib() {
	_init_malloc();
}

static inline uint32_t syscall0(uint32_t syscall_num) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num):"memory");
	return retval;
}

static inline uint32_t syscall1(uint32_t syscall_num, uint32_t param1) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1):"memory");
	return retval;
}

static inline uint32_t syscall2(uint32_t syscall_num, uint32_t param1, uint32_t param2) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2):"memory");
	return retval;
}

static inline uint32_t syscall3(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3) {
	uint32_t retval;
	asm volatile("int $0x80":"=a"(retval):"a"(syscall_num),"b"(param1),"c"(param2),"d"(param3):"memory");
	return retval;
}

void writestring(char *string) {
	syscall1(0,(uint32_t)(uintptr_t)string);
}

uint32_t exec(char *name) {
	return syscall3(1,(uint32_t)(uintptr_t)name,0,0);
}

uint32_t exec_args(char *name, char **arguments, char **environment) {
	return syscall3(1,(uint32_t)(uintptr_t)name,(uint32_t)(uintptr_t)arguments,(uint32_t)(uintptr_t)environment);
}

void exit(uint32_t code) {
	syscall1(2,code);
	while(1);
}

void yield() {
	syscall0(6);
}

uint32_t waitpid(uint32_t pid) {
	syscall1(10,pid);
	return syscall0(11);
}

uint32_t getpid() {
	return syscall0(7);
}

uint32_t fork() {
	return syscall0(25);
}

void *map_mem(void *address) {
	return (void *)(uintptr_t)syscall1(26,(uint32_t)(uintptr_t)address);
}