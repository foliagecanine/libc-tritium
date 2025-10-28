#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

char* strchr(const char *s, int c)
{
	while ((*s) != (char)c)
		if (!(*s++)) return 0;
	return (char *)s;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
