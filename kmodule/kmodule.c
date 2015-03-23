/*
** kmodule.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 07:01:30 2015 eax
** Last update Mon Mar 23 12:35:01 2015 
*/

#include <elf/elf.h>
#include <utils/error.h>
#include <utils/print.h>
#include <kmodule/kmodule.h>
#include <initrd/initrd.h>
#include <utils/assert.h>
#include <utils/string.h>
#include <process/process.h>

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

int	kmodule_bind_got_relplt(Elf32_Ehdr *h, t_elfparse *ep, t_elfparse_symb *ksym)
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


int	kmodule_bind_got_reldyn(Elf32_Ehdr *h, t_elfparse *ep, t_elfparse_symb *ksym)
{
  int sz;
  t_elfparse_sections *secs;

  secs = &ep->sections;
  sz = secs->reldyn->sh_size / secs->reldyn->sh_entsize - 1;

  for ( ; sz >= 0 ; --sz)
    {
      
      Elf32_Rel *rel = (Elf32_Rel *)((int)h + secs->reldyn->sh_offset) + sz;
      
      Elf32_Shdr *tab = elf_section(h, secs->reldyn->sh_link);
      Elf32_Sym *newsymbol = ((Elf32_Sym *)((int)h + tab->sh_offset)) + ELF32_R_SYM(rel->r_info);
      /* printf("%x %x %x\n", rel, tab, newsymbol); */
      if (ELF32_R_TYPE(rel->r_info) != R_386_GLOB_DAT)
	continue;
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


int	kmodule_bind_got(Elf32_Ehdr *h, t_elfparse *ep, t_elfparse_symb *ksym)
{
  if (ep->sections.relplt)
    kmodule_bind_got_relplt(h, ep, ksym);
  if (ep->sections.reldyn)
    kmodule_bind_got_reldyn(h, ep, ksym);
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

void	kmodule_exec(t_elfparse *ep, enum e_kmod_exec mode)
{
  int	(*the_init_func)(void*);
  char	c;

  c = 0;
  the_init_func = (void*)ep->entry;
  if (mode == KMODULE_EXEC_KERNELLAND)
    the_init_func(&c);
  else
    create_process(the_init_func);
}


int	kmodule_load(t_initrd_kmod *km, t_elfparse_symb **ksym)
{
  memset((u32)&km->ep, 0, sizeof(km->ep));

  printf("Loading %s", km->name);
  if (kmodule_parse(km->data, &km->ep, ksym) == -1)
    return (reter(1, "Fail when loading module"));
  printf(" to %x\n", km->ep.entry);
  t_elfparse_symb	*s = km->ep.symb;
  while (s)
    {

      if (s->addr && !kresolve_symb(s->name, *ksym))
	{
	  /* printf("adding [%s] (%x) from [%s]\n", s->name, s->addr, km->name); */
	  add_symb(ksym, s->name, s->addr);
	}
      s = s->next;
    }
  return (0);
}


int	kmodule_load_all(t_initrd_kmod *km, t_elfparse_symb **ksym)
{
  while (km)
    {
      if (kmodule_load(km, ksym) == -1)
	return (-1);
      km = km->next;
    }
  return (0);
}

int	kmodule_load_by_name(char *name,
			     t_initrd_kmod *km,
			     t_elfparse_symb **ksym)
{
  while (km)
    {
      if (!strcmp(km->name, name))
	kmodule_load(km, ksym);
      km = km->next;
    }
  return (0);
}

int	kmodule_exec_by_name(char *name,
			     t_initrd_kmod *km, enum e_kmod_exec mode)
{
  while (km)
    {
      if (!strcmp(km->name, name))
	kmodule_exec(&km->ep, mode);
      km = km->next;
    }
  return (0);
}
