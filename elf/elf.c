/*
** elf.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Feb 21 20:57:11 2015 eax
** Last update Mon Feb 23 07:23:50 2015 eax
*/

#include <utils/types.h>
#include <utils/error.h>
#include <utils/string.h>
#include <memory/kmalloc.h>
#include <elf/elf.h>
#include <elf/elf_internal.h>

Elf32_Shdr	*elf_sheader(Elf32_Ehdr *h)
{
  return ((Elf32_Shdr *)((int)h + h->e_shoff));
}

Elf32_Shdr	*elf_section(Elf32_Ehdr *h, int idx)
{
  return (elf_sheader(h) + idx);
}

char	*elf_str_table(Elf32_Ehdr *h)
{
  if(h->e_shstrndx == SHN_UNDEF)
    return (NULL);
  return ((char *)h + elf_section(h, h->e_shstrndx)->sh_offset);
}

char	*elf_lookup_string(Elf32_Ehdr *h, int off)
{
  char *strtab = elf_str_table(h);
  
  if(strtab == NULL)
    return (NULL);
  return (strtab + off);
}

int	elf_parse_header(Elf32_Ehdr *h, t_elfparse *ep)
{
  if (memcmp(h->e_ident, ELFMAG, SELFMAG) != 0)
    return (reter(-1, "Bad magic elf"));
  
  if (h->e_ident[EI_CLASS] != ELFCLASS32)
    return (reter(-1, "Only 32b is supported"));

  if (h->e_ident[EI_DATA] != ELFDATA2LSB)
    return (reter(-1, "Only LSB is supported"));

  if (h->e_machine != EM_386)
    return (reter(-1, "Only Intel 80386 is supported"));

  if (h->e_version != EV_CURRENT)
    return (reter(-1, "Woot, this ELF version do not exist YET!"));

  ep->entry = (u32)h + h->e_entry;
  
  return (0);
}

int	elf_parse_symb(Elf32_Ehdr *h, t_elfparse *ep)
{
  int sz;
  t_elfparse_sections *secs;

  secs = &ep->sections;
  sz = secs->symtab->sh_size / secs->symtab->sh_entsize;
  ep->nb_alloc_symb = sz;
  ep->symb = kmalloc(sizeof(*ep->symb) * ep->nb_alloc_symb);
	  
  for ( ; sz >= 0 ; --sz)
    {
      Elf32_Sym *sym = (Elf32_Sym *)((int)h + secs->symtab->sh_offset) + sz;
      char	*name = (char *)h + secs->strtab->sh_offset + sym->st_name;

      if (ELF32_ST_BIND(sym->st_info) != STB_GLOBAL)
	continue;
	      
      if (ELF32_ST_TYPE(sym->st_info) == STT_FUNC
	  || (ELF32_ST_TYPE(sym->st_info) == STT_NOTYPE
	      && sym->st_shndx == SHN_UNDEF))
	{
	  ep->symb[ep->nb_symb].name = name;
	  if (sym->st_value == SHN_UNDEF)
	    ep->symb[ep->nb_symb].addr = 0;
	  else
	    ep->symb[ep->nb_symb].addr = (int)h + sym->st_value;
	  ep->nb_symb++;
	}
    }
  return (0);
}

int	elf_parse_sections(Elf32_Ehdr *h, t_elfparse *ep)
{
  unsigned i;
  Elf32_Shdr *sh;

  sh = elf_sheader(h);
  for (i = 0 ; i < h->e_shnum ; i++)
    {
      Elf32_Shdr *sec = sh + i;
      char *name = elf_lookup_string(h, sec->sh_name);
      if (sec->sh_type == SHT_SYMTAB && !strcmp(name, ".symtab"))
	{
	  ep->sections.symtab = sec;
	  ep->sections.strtab = elf_section(h, sec->sh_link);
	}
      else if (sec->sh_type == SHT_REL && !strcmp(name, ".rel.plt"))
	ep->sections.relplt = sec;
      else if (sec->sh_type == SHT_PROGBITS && !strcmp(name, ".got.plt"))
	ep->sections.gotplt = sec;
      else if (sec->sh_type == SHT_PROGBITS && !strcmp(name, ".plt"))
	ep->sections.plt = sec;
    }
  if (!ep->sections.symtab)
    return (reter(-1, "No .symtab found"));
  if (!ep->sections.relplt)
    return (reter(-1, "No .relplt found"));
  if (!ep->sections.gotplt)
    return (reter(-1, "No .got.plt found"));
  if (!ep->sections.plt)
    return (reter(-1, "No .plt found"));
  return (0);
}
