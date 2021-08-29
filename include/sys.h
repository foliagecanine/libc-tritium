#ifndef _SYS_H
#define _SYS_H

uint32_t _syscall0(uint32_t syscall_num);
uint32_t _syscall1(uint32_t syscall_num, uint32_t param1);
uint32_t _syscall2(uint32_t syscall_num, uint32_t param1, uint32_t param2);
uint32_t _syscall3(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3);
uint32_t _syscall4(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4);
uint32_t _syscall5(uint32_t syscall_num, uint32_t param1, uint32_t param2, uint32_t param3, uint32_t param4, uint32_t param5);

void writestring(char *string);
uint32_t exec(char *name);
uint32_t exec_args(char *name, char **arguments, char **environment);
void yield();
uint32_t waitpid(uint32_t pid);
uint32_t getpid();
uint32_t fork();
void *map_mem(void *address);
uint64_t get_ticks();

#endif
