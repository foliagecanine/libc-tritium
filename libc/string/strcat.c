#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

char *strcat(char *s1, const char *s2) {
	strcpy(s1+strlen(s1),s2);
	return s1;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
