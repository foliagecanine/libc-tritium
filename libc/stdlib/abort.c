#include <stdlib.h>
#include <stdio.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

void abort() {
	exit(134);
}

void _assert(const char *expr, const char *file, const char *line) {
	printf("Assertion failed: %s, file %s, line %d", expr, file, line);
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
