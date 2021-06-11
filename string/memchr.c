#include <string.h>

char* memchr(const char *s, int c, int n)
{
	while (n--) {
		if ((*s++) - c)
			return (char *)s;
	}
	return NULL;
}
