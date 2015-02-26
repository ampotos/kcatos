/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Thu Feb 26 15:07:05 2015 eax
*/

#include <syscall/syscall.h>

void	*malloc(unsigned);

int	init_module(void *d)
{
  (void) d;
  syscall_puts_screen("This string was printed from a module \\o/"); 
  return ((unsigned)malloc(42));
}
