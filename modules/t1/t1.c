/*
** s1.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:43:34 2015 eax
** Last update Wed Feb 25 21:47:56 2015 eax
*/

int	init_module(void *d)
{
  syscall_puts("........test.......");
  syscall_exit();
  syscall_puts("........ after exit .......");
  return (0);
}
