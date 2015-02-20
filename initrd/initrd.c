/*
** initrd.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 23:15:22 2015 eax
** Last update Fri Feb 20 23:25:10 2015 eax
*/

#include <fs/tar/tar.h>
#include <utils/print.h>

void	load_initrd(u32 addr)
{
  t_tar_node n;

  get_next_tar_node((char *)addr, NULL);
  while (get_next_tar_node(NULL, &n))
    {
      printf("filename: [%s] ", n.header.name);
      printf("size: [%d]\n", n.header.size);
      puts("==== start content ====");
      printf("%s", n.data);
      puts("==== end content ====");
    }
}
