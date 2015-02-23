/*
** kmodule.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 07:01:30 2015 eax
** Last update Mon Feb 23 07:21:11 2015 eax
*/

#include <elf/elf.h>
#include <utils/error.h>
#include <utils/print.h>
#include <kmodule/kmodule.h>


int	kmodule_bind_got(Elf32_Ehdr *h, t_elfparse *ep)
{
  int sz;
  t_elfparse_sections *secs;
  
  secs = &ep->sections;
  sz = secs->relplt->sh_size / secs->relplt->sh_entsize;
  
  for ( ; sz >= 0 ; --sz)
    {
      Elf32_Rel *rel = (Elf32_Rel *)((int)h + secs->relplt->sh_offset) + sz;

      if (ELF32_R_SYM(rel->r_info) == SHN_UNDEF)
	continue;
      
      Elf32_Shdr *tab = elf_section(h, secs->relplt->sh_link);
      Elf32_Sym *newsymbol = ((Elf32_Sym *)((int)h + tab->sh_offset)) + ELF32_R_SYM(rel->r_info);
      if (newsymbol->st_shndx == SHN_UNDEF)
	{
	  printf("Need to do the undef thing\n");
	  /* todo handle undef */
	}
      else
	*(unsigned*)((int)h + rel->r_offset) = newsymbol->st_value + (int)h;
    }
  return (0);
}

int	kmodule_parse(char *data, t_elfparse *ep)
{
  Elf32_Ehdr *h;
  
  h = (Elf32_Ehdr*)data;
  if (elf_parse_header(h, ep) < 0)
    return (-1);

  if (elf_parse_sections(h, ep) < 0)
    return (-1);
  
  if (elf_parse_symb(h, ep) < 0)
    return (-1);

  if (kmodule_bind_got(h, ep) < 0)
    return (-1);

  return (0);
}

void	kmodule_exec(t_elfparse *ep)
{
  int	(*the_init_func)(void*);
  char	c;

  c = 0;
  the_init_func = (void*)ep->entry;
  printf("ret: %d\n", the_init_func(&c));
}


int	kmodule_load(char *p)
{
  t_elfparse	ep;

  
  memset((u32)&ep, 0, sizeof(ep));
  
  if (kmodule_parse(p, &ep) == -1)
    return (reter(1, "Fail when loading module"));

  printf("entry: %x\n", ep.entry);

  printf("nb_symb: %d\n", ep.nb_symb);
  unsigned	i;
  for (i = 0 ; i < ep.nb_symb ; i++)
    printf("[%s] [%x]\n",  ep.symb[i].name, ep.symb[i].addr);

  puts("Time to exec the module code now!");
  kmodule_exec(&ep);
  
  return (0);
}
