#ifndef _STDLIB_H
#define _STDLIB_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <sys.h>

void _init_malloc();
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t num, size_t size);

unsigned long int strtoul (const char *str, char **endptr, int base);
long int strtol (const char *str, char **endptr, int base);
unsigned long long int strtoull (const char *str, char **endptr, int base);
long long int strtoll (const char *str, char **endptr, int base);
int atoi (const char *str);

char *getenv(char *name);
void exit(uint32_t code);

#endif
