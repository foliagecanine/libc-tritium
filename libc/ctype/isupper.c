#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int isupper(int c) {
	unsigned char uc = (unsigned char)c;
	if (uc >= 'A' && uc <= 'Z')
		return 1;
	return 0;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
