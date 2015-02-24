/*
** pit.c for KCatOS in /home/ampotos/kcatos/descriptor_tables/pic
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Sat Feb 21 19:11:23 2015 
** Last update Wed Feb 25 00:26:12 2015 
*/

#include <utils/types.h>
#include <utils/print.h>
#include <utils/io.h>
#include <descriptor_tables/pic/pic.h>

t_ticks ticks;

void setup_pit(u32 freq)
{
  u32	div = 1193180 / freq;

  io_out(0x43, 0x36);
  io_out(0x40, div & 0xff);
  io_out(0x40, (div >> 8) & 0xff);
}
