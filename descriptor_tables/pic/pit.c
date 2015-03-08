/*
** pit.c for KCatOS in /home/ampotos/kcatos/descriptor_tables/pic
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Sat Feb 21 19:11:23 2015 
** Last update Sun Mar  8 19:03:15 2015 
*/

#include <utils/types.h>
#include <utils/print.h>
#include <utils/io.h>
#include <descriptor_tables/pic/pic.h>

t_ticks g_pit_ticks;

void	 setup_pit(u32 freq)
{
  u32	div = 1193180 / freq;

  io_out(0x43, 0x36);
  io_out(0x40, div & 0xff);
  io_out(0x40, (div >> 8) & 0xff);
}

u32	get_ticks_low() // TODO maybe remove this when module can access to global
{
  return (g_pit_ticks.low);
}


void	pit_handler()
{
  incr_pit();
}

void		sleep(u32 time) // time should be in ms because pit freq is 1kh
{
  t_ticks	end_ticks = g_pit_ticks;  

  end_ticks.low += time;
  if (end_ticks.low < g_pit_ticks.low) // overflow on low 32bit
    end_ticks.high++;
  while (g_pit_ticks.high < end_ticks.high || g_pit_ticks.low < end_ticks.low)
    asm volatile ("hlt");
}
