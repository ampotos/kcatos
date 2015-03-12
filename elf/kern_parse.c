/*
** kern_parse.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 07:59:43 2015 eax
** Last update Thu Mar 12 11:36:28 2015 eax
*/

#include <multiboot.h>
#include <utils/types.h>
#include <elf/elf_internal.h>
#include <elf/elf.h>
#include <utils/assert.h>

int	kern_parse(t_multiboot *multiboot, t_elfparse *ep)
{
  Elf32_Shdr *shdr;
  Elf32_Word shstrtab;

  shdr = (Elf32_Shdr*)multiboot->addr;
  shstrtab = shdr[multiboot->shndx].sh_addr;

  if (elf_parse_sections_noh(shdr, shstrtab, multiboot->num, ep) < 0)
    return (-1);

  if (elf_parse_symb_noh(ep) < 0)
    return (-1);

  return (0);
}
