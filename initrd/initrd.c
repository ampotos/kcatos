/*
** initrd.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 23:15:22 2015 eax
** Last update Mon Feb 23 06:02:39 2015 eax
*/

#include <fs/tar/tar.h>
#include <utils/print.h>
#include <elf/elf.h>


void	load_initrd(u32 addr)
{
  t_tar_node n;
  u32	(*init_the_module)(u32);
  
  get_next_tar_node((char *)addr, NULL);
  while (get_next_tar_node(NULL, &n))
    {
      puts("============================");
      printf("filename: [%s] ", n.header.name);
      printf("size: [%d]\n", n.header.size);
      printf("size: [%s]\n", n.raw_header.size);
      if (!strcmp(n.header.name, "s1.kso"))
	{
	  printf("Ok, let's parse this elf\n"); 
	  kmodule_load(n.data);
	}
      /* puts("==== start content ===="); */
      /* printf("%s", n.data); */
      /* puts("==== end content ===="); */
    }
}
