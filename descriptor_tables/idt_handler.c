/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Tue Dec  9 16:40:40 2014 
*/

#include "idt.h"

void	interrupt_handler(regs_t regs)
{
  terminal_writestring("\nin interrupt handler\n");
  while (1);
}
