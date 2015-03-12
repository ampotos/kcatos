/*
** slides.c for  in /home/eax/dev/kcatos/modules/slides
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Mar 12 11:48:37 2015 eax
** Last update Thu Mar 12 12:51:10 2015 eax
*/

#ifdef TEST_LINUX
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
#else
 #include <syscall/syscall.h>
 #include <utils/string.h>
#endif

#include "slides.h"

extern t_slide g_slides[];

void	print_slide(t_slide *slide)
{
  for (int i = 0 ; i < NB_LINE ; i++)
    {
      char *s = slide->lines[i];
      syscall_write_screen(s, strlen(s));
      if (i != NB_LINE - 1)
	syscall_write_screen("\n", 1);
    }
    /* syscall_puts_screen("bla"); */
}

void	launch_slides(int from)
{
  for (int i = from ; g_slides[i].lines[0] ; i++)
    /* printf("%p\n", g_slides[i].lines[0]); */
    print_slide(&g_slides[0]);
}

int	init_module(void *d)
{
  int	n;
  (void) d;
  /* n = (int)d; */
  n = 0;
  launch_slides(n);
  syscall_puts_screen("Slides finish");
  return (0);
}
