/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Tue Dec 16 12:25:13 2014 
*/

#include "idt.h"
#include "../utils/Print.h"

void		panic_print(regs_t reg);

void	interrupt_handler(regs_t regs)
{
  panic_print(regs);
  while (1);
}
