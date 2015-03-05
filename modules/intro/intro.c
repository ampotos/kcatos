/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Thu Mar  5 11:32:02 2015 
*/

#include <syscall/syscall.h>

void	my_shell();

int	init_module(void *d)
{
  int	stop;

  (void) d;
  syscall_puts_screen("Hi. This is KCatOs. Deal with it.\nYou can type somethinf and read it\n");
  while(45)
    {
      char c;
      read(&c, 1);
      printf("%c\n", (int)c);
    }
  return (0);
}
