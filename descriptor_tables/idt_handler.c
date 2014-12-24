/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Wed Dec 24 16:51:14 2014 eax
*/

#include "idt.h"
#include <utils/Print.h>
#include <utils/usefull_routine.h>

void		panic_print(regs_t reg);

void	interrupt_handler(regs_t regs)
{
  panic_print(regs);
  wait_until_the_end_of_your_life();
}
