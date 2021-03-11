#include <string.h>

char *strncpy(char *dest, const char *src, size_t n)
{
   char *ptr = dest;
   while(n-- && (*(dest++) = *(src++)));
   return ptr;
}
