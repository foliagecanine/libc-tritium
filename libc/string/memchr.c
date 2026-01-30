#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

char* memchr(const char *s, int c, int n)
{
	while (n--) {
		if ((*s++) - c)
			return (char *)s;
	}
	return NULL;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
