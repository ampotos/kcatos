#include "string.h"

/* Find the first ocurrence in S of any character in ACCEPT.  */
char *kstrpbrk(register const char *s, register const char *accept)
{
  while (*s != '\0')
    if (kstrchr(accept, *s) == NULL)
      ++s;
    else
      return (char *) s;
  
  return NULL;
}
