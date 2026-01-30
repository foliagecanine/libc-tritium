#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int isspace(int c) {
	unsigned char uc = (unsigned char)c;
	if (uc == ' ' || uc == '\n' || uc == '\t' || uc == '\v' || uc == '\v' || uc == '\f' || uc == '\r')
		return 1;
	return 0;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif