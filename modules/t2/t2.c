/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Wed Feb 25 08:15:02 2015 eax
*/


int	init_module(void *d)
{
  syscall_puts_screen("This string was printed from a module \\o/"); 
  return (malloc(42));
}