/*
** frame.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Dec 29 00:49:48 2014 eax
** Last update Mon Feb  9 20:57:10 2015 eax
*/

#ifndef FRAME_H_
#define FRAME_H_

#include <memory/page.h>

#define PHYSICAL_MEMORY_SIZE (0x1000000)

typedef struct
{
  char	*used_frames;
  u32	nb_frames;
} t_frames;

void    init_frame();
void    alloc_frame(t_page *page, int kernel_lvl, int writeable);
void    free_frame(t_page *page);

#endif
