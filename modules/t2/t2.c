/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Wed Feb 25 05:31:33 2015 eax
*/


int	puts(char *);

void	do_something(void *d)
{
  *(char *)d = 42;
}

int	init_module(void *d)
{
  volatile int	r;

  do_something(d);
  syscall_puts_screen("This string was printed from a module \\o/");
  return (r);
}
