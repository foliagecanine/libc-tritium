#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int iscntrl(int c) {
	unsigned char uc = (unsigned char)c;
	if (uc < ' ' || uc == 0x7f)
		return 1;
	return 0;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif