/*
** kmodule.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 07:01:30 2015 eax
** Last update Wed Feb 25 05:37:00 2015 eax
*/

#include <elf/elf.h>
#include <utils/error.h>
#include <utils/print.h>
#include <kmodule/kmodule.h>
#include <initrd/initrd.h>
#include <utils/assert.h>

u32	kresolve_symb(char *name, t_elfparse_symb *sym)
{
  while (sym)
    {
      if (!strcmp(name, sym->name))
	return (sym->addr);
      sym = sym->next;
    }
  return (0);
}

int	kmodule_bind_got(Elf32_Ehdr *h, t_elfparse *ep, t_elfparse_symb *ksym)
{
  int sz;
  t_elfparse_sections *secs;

  secs = &ep->sections;
  sz = secs->relplt->sh_size / secs->relplt->sh_entsize - 1;

  for ( ; sz >= 0 ; --sz)
    {
      
      Elf32_Rel *rel = (Elf32_Rel *)((int)h + secs->relplt->sh_offset) + sz;
      if (ELF32_R_SYM(rel->r_info) == SHN_UNDEF)
	{
	  printf("Skipping undef symb\n");
	  continue;
	}
      
      Elf32_Shdr *tab = elf_section(h, secs->relplt->sh_link);
      Elf32_Sym *newsymbol = ((Elf32_Sym *)((int)h + tab->sh_offset)) + ELF32_R_SYM(rel->r_info);
      if (newsymbol->st_shndx == SHN_UNDEF)
	{
	  Elf32_Sym *newrealsymbol = ((Elf32_Sym *)((int)h + secs->dynsym->sh_offset)) + ELF32_R_SYM(rel->r_info);
	  char	*name = (char *)h + secs->dynstr->sh_addr + newrealsymbol->st_name;

	  *(unsigned*)((int)h + rel->r_offset) = kresolve_symb(name, ksym);
	}
      else
	*(unsigned*)((int)h + rel->r_offset) = newsymbol->st_value + (int)h;
    }
  return (0);
}

int	kmodule_parse(char *data, t_elfparse *ep, t_elfparse_symb **ksym)
{
  Elf32_Ehdr *h;
  
  h = (Elf32_Ehdr*)data;
  if (elf_parse_header(h, ep) < 0)
    return (-1);

  if (elf_parse_sections(h, ep) < 0)
    return (-1);
  
  if (elf_parse_symb(h, ep) < 0)
    return (-1);

  if (kmodule_bind_got(h, ep, *ksym) < 0)
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


int	kmodule_load(t_initrd_kmod *km, t_elfparse_symb **ksym)
{
  t_elfparse	ep;
  

  while (km)
    {
      memset((u32)&ep, 0, sizeof(ep));

      printf("Loading %s\n", km->name);
      if (kmodule_parse(km->data, &ep, ksym) == -1)
	return (reter(1, "Fail when loading module"));

      t_elfparse_symb	*s = ep.symb;
      while (s)
	{
	  if (s->addr)
	    add_symb(ksym, s->name, s->addr);
	  s = s->next;
	}

      printf("Time to exec the module [%s] code now!\n", km->name);
      kmodule_exec(&ep);
      km = km->next;
    }
  return (0);
}
