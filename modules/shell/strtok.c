#include "string.h"

static char *olds = NULL;

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the last string strtok() was called with is
   used.  For example:
	char s[] = "-abc=-def";
	x = strtok(s, "-");		// x = "abc"
	x = strtok(NULL, "=-");		// x = "def"
	x = strtok(NULL, "=");		// x = NULL
		// s = "abc\0-def\0"
*/

char * kstrtok(register char *s, register const char *delim)
{
  char *token;

  if (s == NULL)
    {
      if (olds == NULL)
	{
	  return NULL;
	}
      else
	s = olds;
    }

  /* Scan leading delimiters.  */
  s += kstrspn(s, delim);
  if (*s == '\0')
    {
      olds = NULL;
      return NULL;
    }

  /* Find the end of the token.  */
  token = s;
  s = kstrpbrk(token, delim);
  if (s == NULL)
    /* This token finishes the string.  */
    olds = NULL;
  else
    {
      /* Terminate the token and make OLDS point past it.  */
      *s = '\0';
      olds = s + 1;
    }
  return token;
}
