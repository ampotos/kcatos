/*
** s1.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:43:34 2015 eax
** Last update Thu Feb 26 15:05:43 2015 eax
*/

#include <syscall/syscall.h>

int	init_module(void *d)
{
  (void) d;  
  syscall_puts_screen("........test.......");
  syscall_exit();
  syscall_puts_screen("........ after exit .......");
  return (0);
}
