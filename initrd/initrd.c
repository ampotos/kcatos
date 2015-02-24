/*
** initrd.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 23:15:22 2015 eax
** Last update Mon Feb 23 07:57:17 2015 eax
*/

#include <fs/tar/tar.h>
#include <utils/print.h>
#include <memory/kmalloc.h>
#include <initrd/initrd.h>

static int	add_kmod(t_initrd_kmod **km, char *name, u32 size, char *data)
{
  t_initrd_kmod	*new;

  new = kmalloc(sizeof(*new));
  if (!new)
    return (-1);

  new->name = name;
  new->size = size;
  new->data = data;
  new->next = *km;
  *km = new;
  return (0);
}

t_initrd	*load_initrd(u32 addr)
{
  t_initrd	*ret;
  t_tar_node	n;

  ret = kmalloc(sizeof(*ret));
  if (!ret)
    return (NULL);
  ret->kmods = NULL;
  get_next_tar_node((char *)addr, NULL);
  while (get_next_tar_node(NULL, &n))
    {
      printf("filename: [%s]\n", n.raw_header.name);
      add_kmod(&ret->kmods, n.raw_header.name, n.header.size, n.data);
      
      break; /* FIXME: Just need to implement the 
		reloc of UNDEF symb in elf and then
		we can remove this break.
	     */
    }
  return (ret);
}
