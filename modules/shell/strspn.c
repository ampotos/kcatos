#include "string.h"

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT.  */
int kstrspn(const char *s, const char *accept)
{
  register const char *p;
  register const char *a;
  register int count = 0;

  for (p = s; *p != '\0'; ++p)
    {
      for (a = accept; *a != '\0'; ++a)
	if (*p == *a)
	  break;
      if (*a == '\0')
	return count;
      else
	++count;
    }

  return count;
}
