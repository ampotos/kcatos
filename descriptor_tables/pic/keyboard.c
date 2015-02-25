/*
** keyboard.c for KcatOS in /home/ampotos/kcatos
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Tue Feb 24 18:25:34 2015 
** Last update Tue Feb 24 22:44:26 2015 
*/

#include <utils/io.h>

char buff[1024];

int ct_read; // TODO faire une struct

void keyboard_handler()
{
  unsigned char	in;
  unsigned char	ctrl;
  
  in = io_in(0x60);
  ctrl = io_in(0x61);
  if (in & 0x80 && ct_read < 1024) // key release
    buff[ct_read++] = in ^ 0x80; // TODO convertion to ascii
  io_out(0x61, ctrl | 0x80);
  io_out(0x61, ctrl);
}
