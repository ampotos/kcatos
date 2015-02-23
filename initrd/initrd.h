/*
** initrd.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 23:20:18 2015 eax
** Last update Mon Feb 23 07:41:12 2015 eax
*/

#ifndef INITRD_H_
#define INITRD_H_

#include <utils/types.h>

typedef struct s_initrd_kmod
{
  char	*name;
  u32	size;
  char	*data;
  struct s_initrd_kmod	*next;
} t_initrd_kmod;

typedef struct
{
  t_initrd_kmod	*kmods;
} t_initrd;

t_initrd	*load_initrd(u32 addr);

#endif
