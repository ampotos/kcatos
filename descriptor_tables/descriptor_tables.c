/*
** descriptor_table.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Dec  5 21:31:02 2014 eax
** Last update Tue Mar 10 11:19:23 2015 eax
*/

#include <descriptor_tables/gdt.h>
#include <descriptor_tables/idt.h>
#include <descriptor_tables/descriptor_tables.h>

void	init_descriptor_tables()
{
  printf("[-] Initalization of gdt:");
  init_gdt();
  puts(" Ok");
  setup_idt();
}
