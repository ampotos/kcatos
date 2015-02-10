/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Tue Feb 10 02:02:22 2015 eax
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
  panic_print(regs);
  wait_until_the_end_of_your_life();
}
