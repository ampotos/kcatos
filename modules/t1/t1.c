/*
** s1.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:43:34 2015 eax
** Last update Sun Feb 22 22:04:11 2015 eax
*/

int	get_ret_val()
{
  return (42);
}

void	do_something(void *d)
{
  *(char *)d = 42;
}

int	init_module(void *d)
{
  volatile int	r;
  
  do_something(d);
  r = get_ret_val();
  return (r);
}
