/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Sun Mar  8 19:09:44 2015 
*/

#include <syscall/syscall.h>

void	my_shell();

int	init_module(void *d)
{
  int	stop;

  (void) d;
  syscall_puts_screen("Going to sleep 2.5s\n");
  syscall_sleep(2500);
  syscall_puts_screen("Hi. This is KCatOs. Deal with it.\nYou can type somethinf and read it\n");
  while(45)
    {
      char c;
      syscall_read(&c, 1);
      printf("%c\n", (int)c);
    }
  return (0);
}
