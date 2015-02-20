/*
** string.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Dec 24 14:31:52 2014 eax
** Last update Fri Feb 20 22:34:57 2015 eax
*/

#ifndef STRING_H_
#define STRING_H_

#include <utils/types.h>

int	strncmp_p(char *s1, char *s2, uint32_t n);
void	memset(uint32_t dst, uint32_t val, uint32_t size);
void	bzero(uint32_t dst, uint32_t size);
void	memcpy(u32 dst, u32 src, u32 size);
#endif
