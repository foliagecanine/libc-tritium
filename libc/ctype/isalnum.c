#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int isalnum(int c) {
	return isalpha(c) || isdigit(c);
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
