#include <stdlib.h>

void abort() {
	exit(134);
}

void _assert(const char *expr, const char *file, const char *line) {
	printf("Assertion failed: %s, file %s, line %d", expr, file, line);
}