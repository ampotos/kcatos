/*
** string.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Dec 24 14:31:52 2014 eax
// Last update Wed Mar  4 23:39:18 2015 
*/

#ifndef STRING_H_
#define STRING_H_

#include <utils/types.h>

int	strncmp_p(char *s1, char *s2, uint32_t n);
void	memset(uint32_t dst, uint32_t val, uint32_t size);
void	bzero(uint32_t dst, uint32_t size);
void	memcpy(void *dst, void *src, u32 size);
int	memcmp(void *s1, void *s2, u32 sz);
int	strcmp(const char *s1, const char *s2);
u32     strlen(const char *s);
u32     is_num_c(u8 c);
u32     is_alpha_c(u8 c);
#endif
