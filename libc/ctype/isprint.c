#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int isprint(int c) {
	return !iscntrl(c);
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif