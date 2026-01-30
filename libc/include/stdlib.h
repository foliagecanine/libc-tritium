#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <stdint.h>

#define assert(e) ((e) ? (void)0 : _assert(#e,__FILE__, __LINE__))

#ifdef __cplusplus
extern "C" {
#endif

void _init_malloc(void);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t num, size_t size);

unsigned long int strtoul (const char *str, char **endptr, int base);
long int strtol (const char *str, char **endptr, int base);
unsigned long long int strtoull (const char *str, char **endptr, int base);
long long int strtoll (const char *str, char **endptr, int base);
int atoi (const char *str);

char *getenv(const char *name);
void exit(uint32_t code);
void abort(void);
void _assert(const char *expr, const char *file, const char *line);

int abs(int i);

void qsort(void * base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));

//TEMPOR#ifdef __cplusplus
#ifdef __cplusplus
}
#endif

#endif
