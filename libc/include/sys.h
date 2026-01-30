#ifndef _SYS_H
#define _SYS_H

#include <stdint.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

enum syscalls {
	SYSCALL_TERMINAL_WRITESTRING = 0,
	SYSCALL_EXEC_SYSCALL = 1,
	SYSCALL_EXIT_PROGRAM = 2,
	SYSCALL_TERMINAL_PUTENTRYAT = 3,
	SYSCALL_GETCHAR = 4,
	SYSCALL_GET_INPUT_DATA = 5,
	SYSCALL_YIELD = 6,
	SYSCALL_GETPID = 7,
	SYSCALL_FREE_PAGES = 8,
	SYSCALL_TERMINAL_OPTION = 9,
	SYSCALL_WAITPID = 10,
	SYSCALL_GET_RETVAL = 11,
	SYSCALL_FOPEN_USERMODE = 12,
	SYSCALL_FREAD_USERMODE = 13,
	SYSCALL_FWRITE_USERMODE = 14,
	SYSCALL_FCREATE_USERMODE = 15,
	SYSCALL_FDELETE_USERMODE = 16,
	SYSCALL_FERASE_USERMODE = 17,
	SYSCALL_READDIR_USERMODE = 18,
	SYSCALL_NULL_FUNCTION_1 = 19,
	SYSCALL_NULL_FUNCTION_2 = 20,
	SYSCALL_NULL_FUNCTION_3 = 21,
	SYSCALL_NULL_FUNCTION_4 = 22,
	SYSCALL_DEBUG_BREAK = 23,
	SYSCALL_GET_TICKS = 24,
	SYSCALL_FORK_PROCESS = 25,
	SYSCALL_MAP_MEM = 26,
	SYSCALL_GRAPHICS_FUNCTION = 27,
	SYSCALL_REGISTER_IPC_PORT = 28,
	SYSCALL_SAFE_DEREG_IPC_PORT = 29,
	SYSCALL_SAFE_RECEIVE_IPC_SIZE = 30,
	SYSCALL_SAFE_TRANSFER_IPC = 31,
	SYSCALL_SAFE_RECEIVE_IPC = 32,
	SYSCALL_WAITIPC = 33,
	SYSCALL_NULL_FUNCTION_5 = 34,
	SYSCALL_NULL_FUNCTION_6 = 35,
	SYSCALL_NULL_FUNCTION_7 = 36,
	SYSCALL_NULL_FUNCTION_8 = 37,
	SYSCALL_SERIAL_PUTCHAR = 38
};

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

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif

#endif
