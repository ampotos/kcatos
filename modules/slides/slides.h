/*
** slides.h for  in /home/eax/dev/kcatos/modules/slides
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Mar 12 11:56:58 2015 eax
** Last update Fri Mar 13 16:30:38 2015 eax
*/

#ifndef SLIDES_H_
#define SLIDES_H_

#define NB_LINE (25)
#define NB_COL (80)

#ifdef TEST_LINUX
#define syscall_puts_screen puts
#define syscall_write_screen(s, n) write(1, s, n)
#endif

typedef struct
{
  int	animations[NB_LINE];
  char	*lines[NB_LINE];
  void (*f_after_line)(int n);
} t_slide;

#endif
