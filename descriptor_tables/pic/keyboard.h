/*
** keyboard.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Feb 25 06:22:30 2015 eax
** Last update Wed Feb 25 07:04:21 2015 eax
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

typedef struct
{
  u32	available;
  u32	read_pos;
  char	buff[1024];
} t_keyboard;

int	keyboard_char_to_read();
int	keyboard_getchar();

#endif
