/*
** descriptor_table.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Dec  5 21:31:02 2014 eax
** Last update Mon Dec  8 19:11:10 2014 
*/

#include "gdt.h"
#include "idt.h"
#include "descriptor_tables.h"

void	init_descriptor_tables()
{
  init_gdt();
  setup_idt();
}
