/*
** keyboard.c for KcatOS in /home/ampotos/kcatos
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Tue Feb 24 18:25:34 2015 
** Last update Thu Mar  5 11:33:13 2015 
*/

#include <utils/io.h>
#include <utils/string.h>
#include <utils/routine.h>
#include <utils/flags.h>
#include <descriptor_tables/pic/keyboard.h>

/* TODO: */
/* 	refaire tout le keyboard mangment plus propre et qui gère plus de truc */

  // TODO one day when we want to have event on keyboard we have to print the raw data input and write it somewhere where userland can read it.

t_keyboard g_keyboard = {0, {}};

void	keyboard_handler()
{
  unsigned char	in;
  unsigned char	ctrl;
  
  in = io_in(0x60);
  ctrl = io_in(0x61);

  if ((in & 0x80) && g_keyboard.available < 1024)
    if ((in ^ 0x80) != 96 || !g_keyboard.available || g_keyboard.buff[g_keyboard.available - 1] != 96)       g_keyboard.buff[g_keyboard.available++] = in ^ 0x80;
  if (!(in & 0x80) && is_special_k(in) && g_keyboard.available < 1024)
    g_keyboard.buff[g_keyboard.available++] = in | 0x80;
  io_out(0x61, ctrl | 0x80);
  io_out(0x61, ctrl);
}


void	keyboard_swap(u32 size)
{
  int	 ct = -1;

  while (++ct + size < g_keyboard.available)
    g_keyboard.buff[ct] = g_keyboard.buff[size + ct];
  g_keyboard.available -= size;
}

void	keyboard_clear_buff(u32 size)
{
  u32	interrupt = get_flags() & INTERRUPT_FLAG;

  if (!interrupt)
    asm volatile ("cli");
  if (size < g_keyboard.available)
    {
      keyboard_swap(size);
      return ;
    }
  g_keyboard.available = 0;
  memset((u32)g_keyboard.buff, 0, sizeof(g_keyboard.buff));
  if (!interrupt)
    asm volatile ("sti");
}

u32	keyboard_available()
{
  char	buff[1024];

  memset((u32)buff, 0, 1024);
  keyboard_ascii_convert(buff, g_keyboard.available, 0);
  return (strlen(buff));
}

u32	keyboard_get_buff(char* buff, u32 size)
{
  u32	real_size;
  u32	size_orig;
  u32	av;
  
  asm volatile ("cli");
  av = keyboard_available();
  real_size = size > av ? av : size;
  size_orig = keyboard_ascii_convert(buff, real_size, 1);
  keyboard_clear_buff(size_orig);
  asm volatile ("sti");
  return (real_size);
}

// next fonction maybe usefull one day

// available to raw buffer
u32	keyboard_available_raw()
{
  return (g_keyboard.available);
}

// get raw buffer
u32	keyboard_get_buff_raw(char* buff, u32 size)
{
  u32	real_size = size > keyboard_available_raw() ? keyboard_available_raw() : size;
  
  memset((u32)buff, 0, 1024);
  asm volatile ("cli");
  memcpy(buff, g_keyboard.buff, real_size);
  keyboard_clear_buff(real_size);
  asm volatile ("sti");
  return (real_size);
}
