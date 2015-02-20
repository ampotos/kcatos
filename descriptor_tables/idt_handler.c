/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Wed Feb 11 18:42:45 2015 
*/

#include "idt.h"
#include <utils/Print.h>
#include <utils/usefull_routine.h>
#include <syscall/syscall_handler.h>

void		panic_print(regs_t reg);

void	interrupt_handler(regs_t regs)
{
  if (regs.int_no == 0x80)
    {
      syscall_handler(&regs);
      return;
    }
  else if (regs.int_no >= 32 && regs.int_no <= 47)
    {
      irq_handler(&regs);
      return ;
    }
  panic_print(regs);
  wait_until_the_end_of_your_life();
}
