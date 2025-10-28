#include <ctype.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int isxdigit(int c) {
	unsigned char uc = (unsigned char)c;
	return (uc >= '0' && uc <= '9') || (uc >= 'A' && uc <= 'F') || (uc >= 'a' && uc <= 'f'); 
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
