#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
