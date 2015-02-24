/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Tue Feb 24 14:35:18 2015 
*/

#include <descriptor_tables/idt.h>
#include <descriptor_tables/pic/pic.h>
#include <utils/print.h>
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
      return;
    }
  panic_print(regs);
  wait_until_the_end_of_your_life();
}
