#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int toupper(int c) {
	if (islower(c))
		return c-'a'+'A';
	return c;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
