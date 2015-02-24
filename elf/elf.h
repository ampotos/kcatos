/*
** elf.h for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 05:47:19 2015 eax
** Last update Mon Feb 23 07:19:05 2015 eax
*/

#ifndef ELF_H_
#define ELF_H_

#include <elf/elf_internal.h>

typedef struct
{
  char	*name;
  unsigned addr;
} t_elfparse_symb;

typedef struct
{
  Elf32_Shdr *symtab;
  Elf32_Shdr *gotplt;
  Elf32_Shdr *relplt;
  Elf32_Shdr *plt;
  Elf32_Shdr *strtab;
} t_elfparse_sections;

typedef struct
{
  unsigned		entry;
  t_elfparse_sections	sections;
  unsigned		nb_symb;
  unsigned		nb_alloc_symb;
  t_elfparse_symb	*symb;
} t_elfparse;



Elf32_Shdr	*elf_sheader(Elf32_Ehdr *h);
Elf32_Shdr	*elf_section(Elf32_Ehdr *h, int idx);
char		*elf_str_table(Elf32_Ehdr *h);
char		*elf_lookup_string(Elf32_Ehdr *h, int off);

int		elf_parse_header(Elf32_Ehdr *h, t_elfparse *ep);
int		elf_parse_symb(Elf32_Ehdr *h, t_elfparse *ep);
int		elf_parse_sections(Elf32_Ehdr *h, t_elfparse *ep);

#endif
