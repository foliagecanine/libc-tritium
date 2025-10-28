#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

char *strncpy(char *dest, const char *src, size_t n)
{
   char *ptr = dest;
   while(n-- && (*(dest++) = *(src++)));
   return ptr;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif

