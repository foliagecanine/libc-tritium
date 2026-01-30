#include <string.h>

//TEMPOR#ifdef __cplusplus
//TEMPORextern "C" {
//TEMPOR#endif

char *strcpy(char *dest, const char *src)
{
   char *ptr = dest;
   while((*(dest++) = *(src++)));
   return ptr;
}

//TEMPOR#ifdef __cplusplus
//TEMPOR}
//TEMPOR#endif
