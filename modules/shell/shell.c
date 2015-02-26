/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Thu Feb 26 15:07:20 2015 eax
*/

#include <syscall/syscall.h>

void	my_read()
{
  int	c;
  int	stop;

  stop = 0;
  while (!stop)
    {
      while (syscall_keyboard_char_to_read())
	{
	  c = syscall_keyboard_getchar();
	  if (c == 0x1c)
	    {
	      stop = 1;
	      syscall_write_screen("\n", 1);
	    }
	  else
	    syscall_write_screen(".", 1);
	}
    }

}

void	my_shell()
{

  while (1)
    {
      syscall_write_screen("$>", 2);
      my_read();

    }
}

int	init_module(void *d)
{
  (void) d;
  my_shell();
  return (0);
}
