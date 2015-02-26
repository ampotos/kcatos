/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Thu Feb 26 15:05:54 2015 eax
*/

#include <syscall/syscall.h>

void	my_shell();

int	init_module(void *d)
{
  int	stop;

  (void) d;
  if (!syscall_is_computer_on())
    if (syscall_is_computer_on_fire())
      {
        syscall_puts_screen("Oh sheat! Fire! Fire! Fire!");
	syscall_puts_screen("Lets get out of there!");
	*((unsigned*)init_module) /= ((unsigned)init_module)&0;
      }

  syscall_puts_screen("Hi. This is KCatOs. Deal with it.");
  syscall_oh_crap();

  stop = 0;
  while (!stop)
    {
      while (syscall_keyboard_char_to_read())
	{
	  syscall_keyboard_getchar();
	  stop = 1;
	}
    }
  syscall_puts_screen("cool");
  my_shell();
  return (0);
}
