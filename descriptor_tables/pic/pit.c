/*
** pit.c for KCatOS in /home/ampotos/kcatos/descriptor_tables/pic
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Sat Feb 21 19:11:23 2015 
** Last update Tue Feb 24 19:12:53 2015 
*/

#include <utils/types.h>


void setup_pit(u32 freq)
{
  u32	div = 1193180 / freq;

  io_out(0x43, 0x36);
  io_out(0x40, div & 0xff);
  io_out(0x40, (div >> 8) & 0xff);
}
