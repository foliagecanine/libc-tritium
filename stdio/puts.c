
#include <stdio.h>

int puts(char *str) {
	while (*str) {
		if (putchar(*str++)==EOF)
			return EOF;
	}
	if (putchar('\n')==EOF)
		return EOF;
}
