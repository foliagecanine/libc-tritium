#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

// Adapted from PDClib

size_t strcspn( const char * s1, const char * s2 )
{
	size_t len = 0;
	const char * p;

	while (s1[len]) {
		p = s2;
		while (*p) {
			if (s1[len] == *p++)
				return len;
		}
		len++;
	}
	return len;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
