/*
** slides.c for  in /home/eax/dev/kcatos/modules/slides
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Mar 12 11:48:37 2015 eax
** Last update Fri Mar 20 18:15:21 2015 
*/

#ifdef TEST_LINUX
 #include <stdio.h>
 #include <unistd.h>
 #include <string.h>
#else
 #include <syscall/syscall.h>
 #include <utils/string.h>
 #include <utils/types.h>
 #include <utils/print.h>
#endif

#include "slides.h"

void	ani_logo(int n)
{
  size_t oldx;
  size_t oldy;
  uint8_t old_color;
  char c;

  if (n == NB_LINE - 1)
    {
      syscall_sleep(500);
      terminal_getpos(&oldx, &oldy);
      old_color = terminal_getcolor();
      for (int i = 0 ; i < 50 ; i++)
	{
	  for (int y = 0 ; y < 25 ; y++)
	    {
	      for (int x = 0 ; x < 80 ; x++)
		{
		  terminal_setpos(x, y);
		  if ((c = get_cur_entry() & 0xff) != ' ')
		    {
		     terminal_setpos(x, y);
		     int r;
		     r = ((i + x + y) * (x*2 + y*3 + i*4));
		     r |= i << 5;
		     r ^= i * x;
		     terminal_setcolor(1 + r % 14);
		     /* syscall_write_screen("KCat.Os." + ((x+i) % 8), 1); */
		     syscall_write_screen(&c, 1);
		     
		    }
		}
	    }
	  syscall_sleep(10);
	}

      for (int i = 0 ; i < 80 ; i++)
	{
	  for (int y = 0 ; y < 25 ; y++)
	    {
	      if (i <= 2)
		{
		  terminal_setpos(41, y);
		  syscall_write_screen("  ", 2);
		}
	      for (int x = 1 ; x <= 41 - (i / 2) ; x++)
		{
		  int r;
		  r = ((i + x + y) * (x*2 + y*3 + i*4));
		  r |= i << 5;
		  r ^= i * x;
		  terminal_setpos(x, y);
		  terminal_setcolor(1 + r % 14);
		  c = get_cur_entry() & 0xff;
		  terminal_setpos(x - 1, y);
		  syscall_write_screen(&c, 1);
		}
	      for (int x = 78 ; x > 40 + (i / 2) ; x--)
		{
		  int r;
		  r = ((i + x + y) * (x*2 + y*3 + i*4));
		  r |= i << 5;
		  r ^= i * x;
		  terminal_setpos(x - 1, y);
		  terminal_setcolor(1 + r % 14);
		  c = get_cur_entry() & 0xff;
		  terminal_setpos(x, y);
		  syscall_write_screen(&c, 1);
		}

	      syscall_sleep(1);
	    }
	  if (i == 9)
	    {
	      terminal_setcolor(15);
	      terminal_setpos(41-4, 12);
	      syscall_write_screen("KCat.Os", 7);
	    }
	}
       
      
      terminal_setpos(oldx, oldy);
      terminal_setcolor(old_color);
    }
}

void	print_slide(t_slide *slide)
{
  for (int i = 0 ; i < NB_LINE ; i++)
    {
      char *s = slide->lines[i];
      syscall_write_screen(s, strlen(s));
      if (i != NB_LINE - 1)
	syscall_write_screen("\n", 1);
      if (slide->f_after_line)
	slide->f_after_line(i);
      syscall_sleep(slide->animations[i]);
    }
  /* syscall_puts_screen("bla"); */
}


void	launch_slides(int from)
{
  char	r;
  t_slide g_slides[] =
  {    
    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	""
      },
    },
    {
      .f_after_line = ani_logo,
      .animations = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50},
      .lines = {
	"                                         ,",
	"                                         @''@",
	"                                         +''''",
	"                                       ;''''''#",
	"                                     #''''''''+",
	"                                    ''''''''''''@",
	"                            `#+';'''''';#@@#@@@#+''#+",
	"                          `'''''''''''''''''''''''''''':",
	"                          @'''''''''''''''''''''''''''''#",
	"                          #''''++''''''''''''''''''''''''+",
	"                      ,@''';'''''''''';'@#''''''''''''''+@@`",
	"                   ;'''''''''''''''''''''''''''''''''''''''''.",
	"                  +'''''''''''''''''''''''''''''''''''''''''''@",
	"                  '''''''''''''''''''''''''''''''''''''''''''''",
	"                   '''''##+###+''''''''''''''''''''''''''''''''",
	"                 `#''''''''''''''''''@#''''''''''''''''''''''@'@",
	"               @''''''''''''''''''''''''''@+'''''''';'#''''''''''@",
	"             .'''''''''''''''''''''''''''''''''''''';''''''''''''''#",
	"             +'''''''''''''''''''''''''''''''''''''''''''''''''''''';",
	"            `'''''''''''''''''''''''''''''''''''''''''''''''''''''''",
	"             +''''''''''''''''''''''''''''''''''''''''''''''''''''#",
	"              +#''''''''''''''''''''''''''''''''''''''''''''''+@+`",
	"                  `.,,'#@@@###+''''''''''''''''''+++##@@@:`",
	"",
	""
      },
    },
    {
      .f_after_line = NULL,
      .animations = {},
      .lines= {NULL}
    }
  };

  for (int i = from ; g_slides[i].lines[0] ; i++)
    {
      print_slide(&g_slides[i]);
      syscall_read(&r, 1);
    }
}

int	init_module(void *d)
{
  int	n;
  (void) d;
  /* n = (int)d; */
  n = 0;
  launch_slides(n);
  launch_future(n);
  syscall_puts_screen("Slides finish");
  return (0);
}