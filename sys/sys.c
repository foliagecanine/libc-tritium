#include <stdio.h>

int envc;
char **envp;

char *getenv(char *name) {
	for (uint32_t i = 0; i < envc; i+=2) {
		if (!strcmp(envp[i],name))
			return envp[i+1];
	}
	return 0;
}

static inline void syscall(unsigned int syscall_num) {
	asm volatile("mov %0,%%eax;int $0x80"::"r"(syscall_num));
}

void writestring(char *string) {
	asm volatile("mov %0,%%ebx"::"r"(string));
	syscall(0);
}

uint32_t exec(char *name) {
	uint32_t retval;
	asm volatile("mov %0,%%ebx; mov $0,%%ecx; mov $0,%%edx"::"r"(name));
	syscall(1);
	asm volatile("mov %%eax,%0":"=m"(retval):);
	return retval;
}

uint32_t exec_args(char *name, char **arguments, char **environment) {
	uint32_t retval;
	asm volatile("pusha; mov %0,%%ebx; mov %1,%%ecx; mov %2,%%edx"::"m"(name),"m"(arguments),"m"(environment));
	syscall(1);
	asm volatile("mov %%eax,%0; popa":"=m"(retval):);
	return retval;
}

void exit(uint32_t code) {
	asm("mov %0,%%ebx; mov $2,%%eax;int $0x80"::"m"(code));
	while(1);
}

void yield() {
	syscall(6);
}

uint32_t waitpid(uint32_t pid) {
	uint32_t retval = 1;
	asm volatile("pusha; mov %0,%%ebx"::"r"(pid));
	syscall(10); //waitpid
	syscall(11); //get_retval
	asm volatile("mov %%eax,%0; popa":"=m"(retval):);
	return retval;
}

uint32_t getpid() {
	uint32_t retval;
	syscall(7);
	asm volatile("mov %%eax,%0":"=m"(retval):);
	return retval;
}

uint32_t fork() {
	uint32_t retval;
	syscall(25);
	asm volatile("mov %%eax,%0":"=m"(retval));
	return retval;
}
