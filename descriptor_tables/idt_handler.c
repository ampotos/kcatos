/*
** idt_handler.c for KCatos in /home/ampotos/kcatos/descriptor_tables
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 19:08:59 2014 
** Last update Tue Feb 10 13:42:28 2015 eax
*/

#include <descriptor_tables/idt.h>
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
  panic_print(regs);
  wait_until_the_end_of_your_life();
}
