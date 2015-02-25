/*
** keyboard.c for KcatOS in /home/ampotos/kcatos
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Tue Feb 24 18:25:34 2015 
** Last update Wed Feb 25 07:04:13 2015 eax
*/

#include <utils/io.h>
#include <utils/string.h>
#include <descriptor_tables/pic/keyboard.h>

t_keyboard g_keyboard = {0, 0, {}};

void	keyboard_handler()
{
  unsigned char	in;
  unsigned char	ctrl;
  
  in = io_in(0x60);
  ctrl = io_in(0x61);
  if (in & 0x80 && g_keyboard.available < 1024) // key release
    g_keyboard.buff[g_keyboard.available++] = in ^ 0x80; // TODO convertion to ascii
  io_out(0x61, ctrl | 0x80);
  io_out(0x61, ctrl);

}

int	keyboard_char_to_read()
{
  if (g_keyboard.read_pos < g_keyboard.available)
    return (1);
  return (0);
}

int	keyboard_getchar()
{
  char	c;
  asm volatile("cli");
  if (!keyboard_char_to_read())
    return (255);

  c = g_keyboard.buff[g_keyboard.read_pos++];
  if (g_keyboard.read_pos == g_keyboard.available)
    {
      g_keyboard.read_pos = 0;
      g_keyboard.available = 0;
      memset((u32)g_keyboard.buff, 0, sizeof(g_keyboard.buff));
    }
  asm volatile("sti");
  return (c);
}
