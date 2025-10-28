#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

void strcut(char* strfrom, char* strto, int from, int to) {
	memcpy( strto, &strfrom[from], to-from );
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
