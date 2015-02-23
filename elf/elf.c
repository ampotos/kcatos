/*
** elf.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Feb 21 20:57:11 2015 eax
** Last update Mon Feb 23 06:03:24 2015 eax
*/

/* #include <sys/types.h> */
/* #include <sys/stat.h> */
/* #include <fcntl.h> */
/* #include <sys/mman.h> */
/* #include <stdlib.h> */
/* #include <stdio.h> */
/* #include <err.h> */
/* #include <string.h> */
#include <utils/types.h>
#include <utils/print.h>
#include <memory/kmalloc.h>
#include <elf/elf_internal.h>

#define BP asm volatile("int $0x3")

typedef struct
{
  char	*name;
  unsigned addr;
} t_module_symb;

typedef struct
{
  Elf32_Shdr *symtab;
  Elf32_Shdr *gotplt;
  Elf32_Shdr *relplt;
  Elf32_Shdr *plt;
  Elf32_Shdr *strtab;
} t_module_sections;

typedef struct
{
  unsigned	entry;
  t_module_sections sections;
  unsigned	nb_symb;
  unsigned	nb_alloc_symb;
  t_module_symb	*symb;
} t_module;


int	reter(int val, char *msg)
{
  printf("%s\n", msg);
  return (val);
}

int	elf_check_valid(Elf32_Ehdr *h)
{
  if (memcmp(h->e_ident, ELFMAG, SELFMAG) != 0)
    return (reter(0, "Bad magic elf"));
  
  if (h->e_ident[EI_CLASS] != ELFCLASS32)
    return (reter(0, "Only 32b is supported"));

  if (h->e_ident[EI_DATA] != ELFDATA2LSB)
    return (reter(0, "Only LSB is supported"));

  if (h->e_machine != EM_386)
    return (reter(0, "Only Intel 80386 is supported"));

  if (h->e_version != EV_CURRENT)
    return (reter(0, "Woot, this ELF version do not exist YET!"));

  return (1);
}

static inline Elf32_Shdr *elf_sheader(Elf32_Ehdr *h) {
  return ((Elf32_Shdr *)((int)h + h->e_shoff));
}

static inline Elf32_Shdr *elf_section(Elf32_Ehdr *h, int idx) {
  return (elf_sheader(h) + idx);
}

static inline char *elf_str_table(Elf32_Ehdr *h) {
  if(h->e_shstrndx == SHN_UNDEF)
    return (NULL);
  return ((char *)h + elf_section(h, h->e_shstrndx)->sh_offset);
}

static inline char *elf_lookup_string(Elf32_Ehdr *h, int off) {
  char *strtab = elf_str_table(h);
  
  if(strtab == NULL)
    return (NULL);
  return (strtab + off);
}

int	kmodule_parse_symb(Elf32_Ehdr *h, t_module *mod)
{
  int sz;
  t_module_sections *secs;

  secs = &mod->sections;
  sz = secs->symtab->sh_size / secs->symtab->sh_entsize;
  mod->nb_alloc_symb = sz;
  mod->symb = kmalloc(sizeof(*mod->symb) * mod->nb_alloc_symb);
	  
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
	  mod->symb[mod->nb_symb].name = name;
	  if (sym->st_value == SHN_UNDEF)
	    mod->symb[mod->nb_symb].addr = 0;
	  else
	    mod->symb[mod->nb_symb].addr = (int)h + sym->st_value;
	  if (!strcmp(name, "init_module"))
	    mod->entry = mod->symb[mod->nb_symb].addr;
	  mod->nb_symb++;
	}
    }
  return (0);
}

int	kmodule_parse_sections(Elf32_Ehdr *h, t_module *mod)
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
	  mod->sections.symtab = sec;
	  mod->sections.strtab = elf_section(h, sec->sh_link);
	}
      else if (sec->sh_type == SHT_REL && !strcmp(name, ".rel.plt"))
	mod->sections.relplt = sec;
      else if (sec->sh_type == SHT_PROGBITS && !strcmp(name, ".got.plt"))
	mod->sections.gotplt = sec;
      else if (sec->sh_type == SHT_PROGBITS && !strcmp(name, ".plt"))
	mod->sections.plt = sec;
    }
  if (!mod->sections.symtab)
    return (reter(-1, "No .symtab found"));
  if (!mod->sections.relplt)
    return (reter(-1, "No .relplt found"));
  if (!mod->sections.gotplt)
    return (reter(-1, "No .got.plt found"));
  if (!mod->sections.plt)
    return (reter(-1, "No .plt found"));
  return (0);
}

int	kmodule_bind_got(Elf32_Ehdr *h, t_module *mod)
{
  int sz;
  unsigned i;
  t_module_sections *secs;
  
  secs = &mod->sections;
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

int	kmodule_parse(char *data, t_module *mod)
{
  Elf32_Ehdr *h;
  
  h = (Elf32_Ehdr*)data;
  if (!elf_check_valid(h))
    return (-1);

  if (kmodule_parse_sections(h, mod) < 0)
    return (-1);
  
  if (kmodule_parse_symb(h, mod) < 0)
    return (-1);

  if (kmodule_bind_got(h, mod) < 0)
    return (-1);

  return (0);
}

void	kmodule_exec(t_module *mod)
{
  int	(*the_init_func)(void*);
  char	c;

  c = 0;
  the_init_func = (void*)mod->entry;
  printf("ret: %d\n", the_init_func(&c));
}


int	kmodule_load(char *p)
{
  t_module	mod;

  
  memset((u32)&mod, 0, sizeof(mod));
  
  if (kmodule_parse(p, &mod) == -1)
    return (reter(1, "Fail when loading module"));

  printf("entry: %x\n", mod.entry);

  printf("nb_symb: %d\n", mod.nb_symb);
  unsigned	i;
  for (i = 0 ; i < mod.nb_symb ; i++)
    printf("[%s] [%x]\n",  mod.symb[i].name, mod.symb[i].addr);

  puts("Time to exec the module code now!");
  kmodule_exec(&mod);
  
  return (0);
}
