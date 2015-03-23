
#include <utils/print.h>
#include <syscall/syscall.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t screen_row = 0;
static size_t screen_col = 0;
static uint8_t screen_color = 0;
//static uint8_t screen_color_save = 0;
static uint16_t *screen_buff = (uint16_t*) 0xB8000;


  /* ----------------------------------- */
 /* Format Functions                    */
/* ----------------------------------- */

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
  return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color)
{
  uint16_t c16 = c;
  uint16_t color16 = color;

  return c16 | color16 << 8;
}


  /* ----------------------------------- */
 /* Setters Functions                   */
/* ----------------------------------- */

void terminal_setcolor(uint8_t color)
{
  screen_color = color;
//  screen_color_save = color;
}

void terminal_fg_setcolor(enum vga_color fg)
{
  terminal_setcolor((screen_color & 240) | fg);
}

void terminal_bg_setcolor(enum vga_color bg)
{
  terminal_setcolor((screen_color & 15) | (bg << 4));
}

uint8_t terminal_getcolor()
{
  return screen_color;
}

enum vga_color terminal_fg_getcolor()
{
  return screen_color & 15;
}

enum vga_color terminal_bg_getcolor()
{
  return (screen_color >> 4) & 15;
}

int terminal_setpos(size_t x, size_t y)
{
  if (x >= VGA_WIDTH || y > VGA_HEIGHT)
    return -1;

  screen_row = y;
  screen_col = x;

  return 0;
}


void terminal_getpos(size_t *x, size_t *y)
{
  *y = screen_row;
  *x = screen_col;
}

uint16_t get_cur_entry()
{
  return screen_buff[screen_row * VGA_WIDTH + screen_col];
}

  /* ----------------------------------- */
 /* Init  Functions                     */
/* ----------------------------------- */

void terminal_initialize()
{
  terminal_setcolor(make_color(COLOR_LIGHT_GREY, COLOR_BLACK));
  clean();
}


  /* ----------------------------------- */
 /* Print Functions Low                 */
/* ----------------------------------- */

void jump_line()
{
  screen_col = 0;

  if (++screen_row != VGA_HEIGHT)
    return ;

  for ( size_t y = 1; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  screen_buff[index - VGA_WIDTH] = screen_buff[index];
	}
    }

  for ( size_t x = 0; x < VGA_WIDTH; x++ )
    {
      const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
      screen_buff[index] = make_vgaentry(' ', 0);
    }

  screen_row--;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;

  screen_buff[index] = make_vgaentry(c, color);
}

void terminal_putchar(const char c)
{
  if (c == '\n' || screen_col == VGA_WIDTH)
    {
      jump_line();
      return;
    }
  if (c == '\t')
    {
	while (screen_col % 4)
	  terminal_putchar(' ');
	return;
    }

  terminal_putentryat(c, screen_color, screen_col++, screen_row);
}


  /* ----------------------------------- */
 /* Recurcive Functions For Print Nb    */
/* ----------------------------------- */

void recurcive_print_int(const uint32_t i)
{
  if (i >= 10)
    recurcive_print_int(i / 10);
  putc('0' + (i % 10));
}

void recurcive_hex(uint32_t i)
{
  char base[] = "0123456789ABCDEF";

  if (i >= 16)
    recurcive_hex(i / 16);
  putc(base[i % 16]);  
}


  /* ----------------------------------- */
 /* Print Functions                     */
/* ----------------------------------- */

// Print Char
void putc(char c)
{
  /* syscall_write_screen(&c, 1); */
  write_screen(&c, 1);
}

// Print String
u32 puts_nolf(const char *data)
{
  size_t i = 0;

  if (data == NULL)
    return (0);
  while (data[i] != '\0')
    putc(data[i++]);
  return (i);
}

u32 puts(const char *data)
{
  u32	ret;
  
  ret = puts_nolf(data);
  putc('\n');
  return (ret + 1);
}

// Print Signed Int 32, 16 and 8 bits
void putd32(int32_t i)
{
  if (i < 0)
    {
      putc('-');
      i *= -1;
    }
  recurcive_print_int(i);
}

void putd16(int16_t i)
{
  putd32((int32_t)i);
}

void putd8(int8_t i)
{
  putd32((int32_t)i);
}

// Print Unsigned Int 32, 16 and 8 bits
void putu32(uint32_t i)
{
  recurcive_print_int(i);
}

void putu16(uint16_t i)
{
  putu32((uint32_t)i);
}

void putu8(uint8_t i)
{
  putu32((uint32_t)i);
}

// Print Unsigned Int in Hex 32, 16 and 8 bits
void puth32(uint32_t i)
{
  uint32_t tmp = 268435455;

  puts_nolf("0x");
  while (i < tmp)
    {
      tmp /= 16;
      putc('0');
    }

  recurcive_hex(i);
}

void puth16(uint16_t i)
{
  uint16_t tmp = 4095;

  puts_nolf("0x");
  while (i < tmp)
    {
      tmp /= 16;
      putc('0');
    }

  recurcive_hex((uint32_t)i);
}

void puth8(uint8_t i)
{
  uint8_t tmp = 16;

  puts_nolf("0x");
  while (i < tmp)
    {
      tmp /= 16;
      putc('0');
    }

  recurcive_hex((uint32_t)i);
}

  /* ----------------------------------- */
 /* Print Functions Hight               */
/* ----------------------------------- */


void printf(char *format, ...)
{
  va_list       params;
  size_t        i = 0;

  va_start(params, format);

  while (format[i] != '\0')
    {
      if (strncmp_p(format + i, "%%", 2))
	{
	  putc('%');
	  i += 2;
	}
      else if (format[i] == '%')
	{
	  i++;
	  // Print Signed Int 8, 16 and 32 bits
	  if (strncmp_p(format + i, "32d", 3))
	    {
	      putd32(va_arg(params, int32_t));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "16d", 3))
	    {
	      putd16(va_arg(params, int));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "8d", 2))
	    {
	      putd8(va_arg(params, int));
	      i += 2;
	    }
	  // Print Unsigned Int 8, 16 and 32 bits
	  else if (strncmp_p(format + i, "32u", 3))
	    {
	      putu32(va_arg(params, uint32_t));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "16u", 3))
	    {
	      putu16(va_arg(params, int));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "8u", 2))
	    {
	      putu8(va_arg(params, int));
	      i += 2;
	    }
	  // Print Unsigned Int 8, 16 and 32 bits in Hex
	  else if (strncmp_p(format + i, "32h", 3))
	    {
	      puth32(va_arg(params, uint32_t));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "16h", 3))
	    {
	      puth16(va_arg(params, int));
	      i += 3;
	    }
	  else if (strncmp_p(format + i, "8h", 2))
	    {
	      puth8(va_arg(params, int));
	      i += 2;
	    }
	  // Print Char
	  else if (format[i] == 'c')
	    {
	      putc(va_arg(params, int));
	      i += 1;
	    }
	  // Print String
	  else if (format[i] == 's')
	    {
	      puts_nolf(va_arg(params, char *));
	      i += 1;
	    }
	  // I like it small !
	  else if (strncmp_p(format + i, "d", 1))
	    {
	      putd32(va_arg(params, int32_t));
	      i += 1;
	    }
	  else if (strncmp_p(format + i, "u", 1))
	    {
	      putu32(va_arg(params, uint32_t));
	      i += 1;
	    }

    else if (strncmp_p(format + i, "x", 1))
      {
        puth32(va_arg(params, int32_t));
        i += 1;
      }

    //else if (strncmp_p(format + i, "k", 1))
    //  {
    //    screen_color_save = screen_color;
    //    screen_color = va_arg(params, int);
    //    i += 1;
    //  }


	  else
	    puts_nolf("???");

    //if (screen_color_save != screen_color)
    //  terminal_setcolor(screen_color_save);
	}
      else
	{
	  putc(format[i]);
	  i++;
	}
    }

  va_end(params);
}


  /* ----------------------------------- */
 /* Print Functions Hight               */
/* ----------------------------------- */

void clean()
{
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  screen_buff[index] = make_vgaentry(' ',  0);
	}
    }
  terminal_setpos(0, 0);
}

size_t		write_screen(char *data, size_t sz)
{
  size_t	i;

  i = 0;
  while (i < sz)
    terminal_putchar(data[i++]);
  return (i);
}

int    draw_window(char *title, size_t pos_x, size_t pos_y, size_t width, size_t height, enum vga_color fg, enum vga_color bg)
{
  int  len = -1;
  int  cnt, line;
  uint8_t  saveColor;

  if (width == 0)
    width = VGA_WIDTH;
  if (height == 0)
    height = VGA_HEIGHT;

  while (title[++len] != '\0');
  len += 6;

  if (len > width || height < 2 || (width + pos_x) > VGA_WIDTH || (height + pos_y) > VGA_HEIGHT)
    return -1;
  saveColor = terminal_getcolor();
  terminal_setcolor(make_color(fg, bg));

  // Head
  terminal_setpos(pos_x, pos_y);
  //putc('┌');
  putc('+');
  for (cnt = (width - len) / 2; cnt > 0; cnt--)
    //putc('─');
    putc('-');
  printf("| %s |", title);
  for (cnt = ((width - len) / 2) + ((width - len) % 2); cnt > 0; cnt--)
    //putc('─');
    putc('-');
  //putc('┐');
  putc('+');

  // Corps
  for (line = height - 2; line > 0; --line)
  {
    terminal_setpos(pos_x, (pos_y + line));
    //putc('│');
    putc('|');
    for (cnt = width - 2; cnt > 0; --cnt)
      //putc(' ');
      putc(' ');
    //putc('│');
    putc('|');
  }

  // Foot
  terminal_setpos(pos_x, (pos_y + height - 1));
  //putc('└');
  putc('+');
  for (cnt = width - 2; cnt > 0; --cnt)
    //putc('─');
    putc('-');
  //putc('┘');
  putc('+');

  terminal_setcolor(saveColor);
  return 0;
}