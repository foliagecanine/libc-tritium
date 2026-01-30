#include <string.h>

#ifdef __cplusplus
#define restrict __restrict
extern "C" {
#endif

void* memcpy(void* restrict dstptr, const void* restrict srcptr, size_t size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (const unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
