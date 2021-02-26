#include <stdio.h>

int putchar(int ic) {
	char c = (char) ic;
	terminal_putchar(c);
	return ic;
}
