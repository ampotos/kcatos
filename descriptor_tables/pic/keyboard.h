/*
** keyboard.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Feb 25 06:22:30 2015 eax
// Last update Wed Mar  4 23:38:03 2015 
*/

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <utils/types.h>

typedef struct
{
  u32	available;
  char	buff[1024];
} t_keyboard;

#define CTRL_R_KMASK	(1 << 0)
#define CTRL_L_KMASK	(1 << 1)
#define MAJ_R_KMASK	(1 << 2)
#define MAJ_L_KMASK	(1 << 3)
#define ALT_GR_KMASK	(1 << 4)
#define ALT_L_KMASK	(1 << 5)
#define MAJ_LOCK_KMASK	(1 << 6)
#define VER_NUM_KMASK	(1 << 7)
#define SUPER_KMASK	(1 << 8)
#define CLICK_KEY_KMASK	(1 << 9)
#define VER_NUM_ACTIVE	(1 << 10)
#define MAJ_LOCK_ACTIVE	(1 << 11)
#define FUCKING_96	(1 << 12)

u32     keyboard_available();
u32     keyboard_get_buff(char* buff, u32 size);
u32     keyboard_available_raw();
u32     keyboard_get_buff_raw(char* buff, u32 size);
void    keyboard_clear_buff(u32 size);

u32     is_special_k(u8 scancode);
u32	keyboard_ascii_convert(char *buff, u32 size, u32 change_state);

extern  t_keyboard g_keyboard;

#endif
