/*
** read.c for KCatOS in /home/ampotos/kcatos
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Thu Feb 26 09:56:04 2015 
** Last update Thu Mar  5 11:37:25 2015 
*/

#include <descriptor_tables/pic/keyboard.h>
#include <utils/types.h>

u32	read_non_block(char *buff, u32 size)
{
  if (!keyboard_available())
    return (0);
  return (keyboard_get_buff(buff, size));
}

u32	read(char *buff, u32 size)
{
  while (!keyboard_available())
    asm volatile ("hlt");
  return (keyboard_get_buff(buff, size));
}

// next fonction maybe usefull one day
u32	read_raw_non_block(char *buff, u32 size)
{
  if (!keyboard_available_raw())
    return (0);
  return (keyboard_get_buff_raw(buff, size));
}

u32	read_raw(char *buff, u32 size)
{
  while (!keyboard_available_raw())
    asm volatile ("hlt");
  return (keyboard_get_buff_raw(buff, size));
}
