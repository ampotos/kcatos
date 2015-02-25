/*
** irq_handler.c for KcatOS in /home/ampotos/kcatos/descriptor_tables/pic
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Wed Feb 11 18:36:18 2015 
** Last update Wed Feb 25 07:07:43 2015 eax
*/

#include <descriptor_tables/idt.h>
#include <descriptor_tables/pic/pic.h>
#include <utils/print.h>
#include <utils/io.h>

static u32 bla;
void	fake_incr_pit()
{
  bla++;
  /* printf("[%d]\n", bla); */
}

static void (*handlers[15])() =
  /* {incr_pit, // pit */
{fake_incr_pit, // pit
   &keyboard_handler, // keyboard
   0};

void	irq_handler(regs_t *regs)
{
  if (handlers[regs->err_code])
    handlers[regs->err_code]();
  else
    {
      printf("IRQ %d handle :\n", regs->err_code);
      printf("Mapped at interruption : %d\n", regs->int_no);
    }
  if (regs->err_code > 7) // send eoi to reunable interrupts
    io_out(0xa0, 0x20);
  io_out(0x20, 0x20);
}
