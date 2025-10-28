#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int tolower(int c) {
	if (isupper(c))
		return c+('a'-'A');
	return c;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
