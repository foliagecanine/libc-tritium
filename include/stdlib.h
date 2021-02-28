#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <sys.h>

void _init_malloc();
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

char *getenv(char *name);
void exit(uint32_t code);

#endif
