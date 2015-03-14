/*
** elf.h for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 05:47:19 2015 eax
** Last update Thu Mar 12 16:38:26 2015 eax
*/

#ifndef ELF_H_
#define ELF_H_

#include <elf/elf_internal.h>
#include <multiboot.h>

typedef struct s_elfparse_symb
{
  char	*name;
  unsigned addr;
  struct s_elfparse_symb *next;
} t_elfparse_symb;

typedef struct
{
  Elf32_Shdr *symtab;
  Elf32_Shdr *gotplt;
  Elf32_Shdr *relplt;
  Elf32_Shdr *reldyn;
  Elf32_Shdr *plt;
  Elf32_Shdr *strtab;
  Elf32_Shdr *dynstr;
  Elf32_Shdr *dynsym;
} t_elfparse_sections;

typedef struct
{
  unsigned		entry;
  t_elfparse_sections	sections;
  /* unsigned		nb_symb; */
  /* unsigned		nb_alloc_symb; */
  t_elfparse_symb	*symb;
} t_elfparse;



Elf32_Shdr	*elf_sheader(Elf32_Ehdr *h);
Elf32_Shdr	*elf_section(Elf32_Ehdr *h, int idx);
char		*elf_str_table(Elf32_Ehdr *h);
char		*elf_lookup_string(Elf32_Ehdr *h, int off);

int		elf_parse_header(Elf32_Ehdr *h, t_elfparse *ep);
int		elf_parse_symb(Elf32_Ehdr *h, t_elfparse *ep);
int		elf_parse_symb_noh(t_elfparse *ep);

int		elf_parse_sections(Elf32_Ehdr *h, t_elfparse *ep);
int		elf_parse_sections_noh(Elf32_Shdr *sh, Elf32_Word shstrtab, u32 num, t_elfparse *ep);
/* void		elfparse_symb_concat(t_elfparse_symb *dst, t_elfparse_symb *src); */
int		kern_parse(t_multiboot *multiboot, t_elfparse *ep);
t_elfparse_symb	*add_symb(t_elfparse_symb **symb, char *name, u32 addr);

#endif
