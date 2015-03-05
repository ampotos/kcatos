/*
** string.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Dec 24 14:23:34 2014 eax
** Last update Wed Mar  4 16:26:03 2015 
*/

#include <utils/types.h>
#include <utils/string.h>

int strncmp_p(char *s1, char *s2, uint32_t n)
{
  if (s1 == NULL || s2 == NULL || *s1 == '\0' || *s2 == '\0' || n == 0)
    return 0;

  n += 1;
  while (--n)
    {
      if (*s1 == '\0' || *s2 == '\0' || *s1 != *s2)
	return 0;
      s1++;
      s2++;
    }
  return 1;
}

void		memset(uint32_t dst, uint32_t val, uint32_t size)
{
  uint32_t	i;
  
  for (i = 0; i < size ; i++)
    ((uint8_t*)dst)[i] = val;
}

void	bzero(uint32_t dst, uint32_t size)
{
  memset(dst, 0, size);
}


void		memcpy(void *dst, void *src, u32 size)
{
  u32	i;
  
  for (i = 0; i < size ; i++)
    ((u8*)dst)[i] = ((u8*)src)[i];
}

int	memcmp(void *s1, void *s2, u32 sz)
{
  while (*(char*)s1 == *(char*)s2 && sz > 0)
    {
      sz--;
      s1++;
      s2++;
    }
  return (sz != 0);
}

int	strcmp(const char *s1, const char *s2)
{
  while (*s1 == *s2 && *s1 && *s2)
    {
      s1++;
      s2++;
    }
  return (*s1 - *s2);
}

u32	strlen(const char *s)
{
  u32	ct = -1;

  while (s[++ct]);
  return (ct);
}

u32	is_num_c(u8 c)
{
  return ((c >= '0' && c <= '9'));
}

u32	is_alpha_c(u8 c)
{
  return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')));
}
