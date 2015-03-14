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
void start_kksh();


/*void	my_shell()
{

  while (1)
    {
      syscall_write_screen("$>", 2);
      syscall_read();

    }
}
*/
int	init_module(void *d)
{
  (void) d;
  //my_shell();
  start_kksh();
  return (0);
}
