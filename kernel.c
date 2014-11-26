#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks if we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

//l14
//c35

static const char *g_logo[] =
  {
    "",
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
    ""
  };




/* Hardware text mode color constants. */
enum vga_color
  {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
  };

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
  static unsigned	i = 0;

  return fg | ((bg == 0) ? ((++i << 5) | ((i*i) >> ((i&1)*2))) % 15 : bg)<< 4;
  /*
  ** "kernel.c:77:30: warning: operation on 'i' may be undefined" said gcc
  ** Perfect, I want this to be the more undefined possible ! :p
  */
}

uint16_t make_vgaentry(char c, uint8_t color)
{
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

size_t strlen(const char* str)
{
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
  return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
  int	i;
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = (uint16_t*) 0xB8000;
  i = 0;
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  i++;
	  terminal_color = make_color(((i << 10) | ((i*i*i*i) >> 2)) % 15, ((i << 5) | ((i*i) >> ((i&1)*2))) % 15);
	  terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
    }
}

void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c)
{
  if (c == '\n')
    {
      terminal_row++;
      terminal_column = 0;
      return;
    }
  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  if ( ++terminal_column == VGA_WIDTH )
    {
      terminal_column = 0;
      if ( ++terminal_row == VGA_HEIGHT )
	{
	  terminal_row = 0;
	}
    }
}

void terminal_writestring(const char* data)
{
  size_t datalen = strlen(data);
  for ( size_t i = 0; i < datalen; i++ )
    terminal_putchar(data[i]);
}

void print_logo(unsigned short of)
{
  unsigned	i;
  unsigned	j;
  unsigned	k;
  unsigned	len;

  for (i = 0 ; i < sizeof(g_logo) / sizeof(*g_logo) ; i++)
    {
      len = strlen(g_logo[i]);
      for (j = 0 ; j <= len ; j++)
	{
	  if (j == len)
	    {
	      while (j++ < VGA_WIDTH - 1)
		{
		  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
		  terminal_putchar(' ');
		}
	      terminal_putchar('\n');
	      break;
	    }
	  k = 0;
	  while (g_logo[i][k] == ' ')
	    k++;
	  int ofj = j + of;
	  if (j < k)
	    ofj = j;
	  else
	    ofj = (j - k + of) % (len - k) + k;
	  if (g_logo[i][ofj] == ' ')
	      terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	  else
	    terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BROWN);
	  if (i == 14 && j >= 38 && j < 45)
	    {
	      terminal_color = make_color(COLOR_RED, COLOR_WHITE);
	      terminal_putchar("KCat.OS"[j-38]);
	    }
	  else	    
	  terminal_putchar(g_logo[i][ofj]);
	}
    }
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
  terminal_initialize();
  terminal_row = 0;
  terminal_column = 0;

  /* terminal_putchar(p); */

  /* Since there is no support for newlines in terminal_putchar yet, \n will
     produce some VGA specific character instead. This is normal. */
  /* terminal_writestring("Hello, KCat.OS world!\n"); */
  /* terminal_writestring("Lorem ipsum dolor sit amet\n"); */
  unsigned short of = 0;
  while (1)
    {
      terminal_row = 0;
      terminal_column = 0;
      /* terminal_initialize(); */
      print_logo(of++);
    }
} 
