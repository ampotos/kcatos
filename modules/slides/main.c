/*
** slides.c for  in /home/eax/dev/kcatos/modules/slides
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Mar 12 11:48:37 2015 eax
** Last update Tue Mar 24 11:50:03 2015 
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
#include <kmodule/kmodule.h>

#define myabs(x) ((x) > 0 ? (x) : -(x))


int	dist_from_center(int x, int y)
{
  int cx = 40;
  int cy = 13;

  double a = 1;
  double b;
  double x2 =  (x - cx)*(x - cx) + (y - cy)*(y - cy);

  double res = 0;
  
  b = x2;
  if (x2 < 0)
    res =  0;
  while (myabs(a-b) > 1)
    {
      a = (a + b) / 2.;
      b = x2 / a;
    }
  res =  a;
  return res;
}


/* void	ani_logo(int n) */
/* { */
/*   size_t oldx; */
/*   size_t oldy; */
/*   uint8_t old_color; */
/*   char c; */

/*   if (n == NB_LINE - 1) */
/*     { */
/*       syscall_sleep(500); */
/*       terminal_getpos(&oldx, &oldy); */
/*       old_color = terminal_getcolor(); */
/*       for (int i = 0 ; i < 50 ; i++) */
/* 	{ */
/* 	  for (int y = 0 ; y < 25 ; y++) */
/* 	    { */
/* 	      for (int x = 0 ; x < 80 ; x++) */
/* 		{ */
/* 		  terminal_setpos(x, y); */
/* 		  if ((c = get_cur_entry() & 0xff) != ' ') */
/* 		    { */
/* 		     terminal_setpos(x, y); */
/* 		     int r; */
/* 		     r = ((i + x + y) * (x*2 + y*3 + i*4)); */
/* 		     r |= i << 5; */
/* 		     r ^= i * x; */
/* 		     terminal_setcolor(1 + r % 14); */
/* 		     /\* syscall_write_screen("KCat.Os." + ((x+i) % 8), 1); *\/ */
/* 		     syscall_write_screen(&c, 1); */
		     
/* 		    } */
/* 		} */
/* 	    } */
/* 	  syscall_sleep(10); */
/* 	} */

/*       for (int i = 0 ; i < 80 ; i++) */
/* 	{ */
/* 	  for (int y = 0 ; y < 25 ; y++) */
/* 	    { */
/* 	      if (i <= 2) */
/* 		{ */
/* 		  terminal_setpos(41, y); */
/* 		  syscall_write_screen("  ", 2); */
/* 		} */
/* 	      for (int x = 1 ; x <= 41 - (i / 2) ; x++) */
/* 		{ */
/* 		  int r; */
/* 		  r = ((i + x + y) * (x*2 + y*3 + i*4)); */
/* 		  r |= i << 5; */
/* 		  r ^= i * x; */
/* 		  terminal_setpos(x, y); */
/* 		  terminal_setcolor(1 + r % 14); */
/* 		  c = get_cur_entry() & 0xff; */
/* 		  terminal_setpos(x - 1, y); */
/* 		  syscall_write_screen(&c, 1); */
/* 		} */
/* 	      for (int x = 78 ; x > 40 + (i / 2) ; x--) */
/* 		{ */
/* 		  int r; */
/* 		  r = ((i + x + y) * (x*2 + y*3 + i*4)); */
/* 		  r |= i << 5; */
/* 		  r ^= i * x; */
/* 		  terminal_setpos(x - 1, y); */
/* 		  terminal_setcolor(1 + r % 14); */
/* 		  c = get_cur_entry() & 0xff; */
/* 		  terminal_setpos(x, y); */
/* 		  syscall_write_screen(&c, 1); */
/* 		} */

/* 	      syscall_sleep(1); */
/* 	    } */
/* 	  if (i == 9) */
/* 	    { */
/* 	      terminal_setcolor(15); */
/* 	      terminal_setpos(41-4, 12); */
/* 	      syscall_write_screen("KCat.Os", 7); */
/* 	    } */
/* 	} */
       
      
/*       terminal_setpos(oldx, oldy); */
/*       terminal_setcolor(old_color); */
/*     } */
/* } */

void	ani_logo(int n)
{
  size_t oldx;
  size_t oldy;
  uint8_t old_color;
  char c;

  /* assert(0); */
  
  if (n == NB_LINE - 1)
    {
      syscall_sleep(100);
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
		     terminal_setcolor(1 + myabs(dist_from_center(x, y) - i) % 14);
		     syscall_write_screen(&c, 1);
		     
		    }
		}
	    }
	  syscall_sleep((i % 10) * 5);
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
  /* ani_logo_end(); */
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
    /* { */
    /*   .f_after_line = NULL, */
    /*   .animations = {}, */
    /*   .lines = { */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"", */
    /* 	"" */
    /*   }, */
    /* }, */

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
      .lines = {
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                               ____  _____ _                                   ",
        "                              |  _ \\|  ___/ \\                                  ",
        "                              | |_) | |_ / _ \\                                 ",
        "                              |  __/|  _/ ___ \\                                ",
        "                              |_|   |_|/_/   \\_\\                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                 ____                                   _   ___                ",
	"                |  _ \\ ___  _   _ _ __ __ _ _   _  ___ (_) |__ \\               ",
        "                | |_) / _ \\| | | | '__/ _` | | | |/ _ \\| |   / /               ",
        "                |  __/ (_) | |_| | | | (_| | |_| | (_) | |  |_|                ",
        "                |_|   \\___/ \\__,_|_|  \\__, |\\__,_|\\___/|_|  (_)                ",
	"                                         |_|                                   ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"                        ___  _     _           _   _  __                         ",
        "                     / _ \\| |__ (_) ___  ___| |_(_)/ _|___                     ",
        "                    | | | | '_ \\| |/ _ \\/ __| __| | |_/ __|                    ",
        "                    | |_| | |_) | |  __/ (__| |_| |  _\\__ \\                    ", 
        "                     \\___/|_.__// |\\___|\\___|\\__|_|_| |___/                    ",
        "                              |__/                                             ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                              Initialisation CPU                               ",
	"                                                                               ",
	"                                                                               ",
	"                             Gestion de la memoire                             ",
	"                                                                               ",
	"                                                                               ",
	"                                   User land                                   ",
	"                                                                               ",
	"                                                                               ",
	"                                   Syscalls                                    ",
	"                                                                               ",
	"                                                                               ",
	"                              Shell et builtins                                ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"                                                                               ",
	"                                                                               ",
	"                     ___  _     _           _   _  __                          ",
        "                    / _ \\| |__ (_) ___  ___| |_(_)/ _|___                     ",
        "                   | | | | '_ \\| |/ _ \\/ __| __| | |_/ __|                   ",
        "                   | |_| | |_) | |  __/ (__| |_| |  _\\__ \\                   ",
        "                    \\___/|_.__// |\\___|\\___|\\__|_|_| |___/                  ",
        "                              |__/                                             ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                         _   _   _       _       _                             ",
        "                        / \\ | |_| |_ ___(_)_ __ | |_ ___                      ",
        "                       / _ \\| __| __/ _ \\ | '_ \\| __/ __|                   ",
        "                      / ___ \\ |_| ||  __/ | | | | |_\\__ \\                   ",
        "                     /_/   \\_\\__|\\__\\___|_|_| |_|\\__|___/                 ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"                            ____                                                 ",
        "                         | __ )  ___  _ __  _   _ ___                          ", 
        "                         |  _ \\ / _ \\| '_ \\| | | / __|                         ",
        "                         | |_) | (_) | | | | |_| \\__ \\                         ",
        "                         |____/ \\___/|_| |_|\\__,_|___/                         ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                **************                                 ",
	"                                * Parser Elf *                                 ",
	"                                **************                                 ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                  ***********                                  ",
	"                                  * Modules *                                  ",
	"                                  ***********                                  ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                            ***********************                            ",
	"                            * Virtual File System *                            ",
	"                            ***********************                            ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"              ___                        _           _   _                       ",
        "           / _ \\ _ __ __ _  __ _ _ __ (_)___  __ _| |_(_) ___  _ __            ",
        "          | | | | '__/ _` |/ _` | '_ \\| / __|/ _` | __| |/ _ \\| '_ \\           ",
        "          | |_| | | | (_| | (_| | | | | \\__ \\ (_| | |_| | (_) | | | |          ",
        "           \\___/|_|  \\__, |\\__,_|_| |_|_|___/\\__,_|\\__|_|\\___/|_| |_|          ",
        "                     |___/                                                     ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                  ********************************************                 ",
	"                  * Kernel :  Kevin Soules et Daniel Mercier *                 ",
	"                  ********************************************                 ",
	"                                                                               ",
	"                                                                               ",
	"               ***************************************************             ",
	"               * Affichage et integration shell : Vincent Lerman *             ",
	"               ***************************************************             ",
	"                                                                               ",
	"                                                                               ",
	"            **********************************************************         ",
	"            * Shell et builtins : Florian Corradin et Simon Daguenet *         ",
	"            **********************************************************         ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"                 ____            _     _  __                                     ",
        "              |  _ \\ _ __ ___ | |__ | | \\_\\ _ __ ___   ___  ___                ", 
        "              | |_) | '__/ _ \\| '_ \\| |/ _ \\ '_ ` _ \\ / _ \\/ __|               ",
        "              |  __/| | | (_) | |_) | |  __/ | | | | |  __/\\__ \\               ",
        "              |_|   |_|  \\___/|_.__/|_|\\___|_| |_| |_|\\___||___/               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                          **************************                           ",
	"                          * Repartition des taches *                           ",
	"                          **************************                           ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
  	"                ____    __                                                       ",
        "             |  _ \\  /_/ _ __ ___   __ _ _ __ _ __ __ _  __ _  ___             ",
        "             | | | |/ _ \\ '_ ` _ \\ / _` | '__| '__/ _` |/ _` |/ _ \\            ",
        "             | |_| |  __/ | | | | | (_| | |  | | | (_| | (_| |  __/            ",
        "             |____/ \\___|_| |_| |_|\\__,_|_|  |_|  \\__,_|\\__, |\\___|            ",
        "                                                        |___/                  ",
	"    +--------------------+                                                     ",
	"    |                    |                                                     ",
	"    | Initialisation CPU +-------+                                             ",
	"    |                    |       |                                             ",
	"    +--------------------+       v                                             ",
	"                           +------------------------+                          ",
	"                           |                        |                          ",
	"                           | Initialisation Memoire +-------+                  ",
	"                           |                        |       |                  ",
	"                           +------------------------+       |                  ",
	"                                                            |                  ",
	"                                                            v                  ",
	"                                             +------------------------+        ",
	"                                             |                        |        ",
	"                                             | Chargement des modules |        ",
	"                                             |                        |        ",
	"                                             +------------------------+        ",
	"                                                                               ",
	"                                                                               "
      }
    },

    {
      .f_after_line = NULL,
      .animations = {},
      .lines = {
	"   _____       _         __               _   _ _ _           _                 ",   
        "| ____|_ __ | |_ _ __ /_/  ___    _   _| |_(_) (_)___  __ _| |_ ___ _   _ _ __ ",
        "|  _| | '_ \\| __| '__/ _ \\/ _ \\  | | | | __| | | / __|/ _` | __/ _ \\ | | | '__|",
        "| |___| | | | |_| | |  __/  __/  | |_| | |_| | | \\__ \\ (_| | ||  __/ |_| | |   ",
        "|_____|_| |_|\\__|_|  \\___|\\___|   \\__,_|\\__|_|_|_|___/\\__,_|\\__\\___|\\__,_|_|   ",
	"                                                                               ",
	"                                                                               ",
	"  +-----------------------+                                                    ",
	"  |                       |  Scancode                                          ",
	"  | Appuie sur une touche +--------+                                           ",
	"  |                       |        |                                           ",
	"  +-----------------------+        |                                           ",
	"                                   v                                           ",
	"                              +--------+                                       ",
	"                              |        |     Traduit en ASCII                  ",
	"                              | Driver +-----------------+                     ",
	"                              |        |                 |                     ",
	"                              +--------+                 |                     ",
	"                                                         v                     ",
	"                                                 +---------------------+       ",
	"                                                 |                     |       ",
	"                                                 | Programme User Land |       ",
	"                                                 |                     |       ",
	"                                                 +---------------------+       ",
	"                                                                               " 
      }
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
      if (r == 'p' && i > 0)
	i -= 2;
    }
}

int	init_module(void *d)
{
  int	n;
  (void) d;
  /* n = (int)d; */
  n = 0;
  clean();
  launch_slides(n);
  start_kksh();
  launch_future(n);
  syscall_puts_screen("Slides finish");
  return (0);
}
