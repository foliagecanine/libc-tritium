#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

int strcmp(const char *s1, const char *s2) {
	size_t len = 0;
	while(s1[len]&&s2[len++])
		if (s1[len]-s2[len]) return s1[len]-s2[len];
	return 0;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
