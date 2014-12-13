#include "Print.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static size_t screen_row = 0;
static size_t screen_col = 0;
static uint8_t screen_color = 0;
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
}

int terminal_setpos(size_t x, size_t y)
{
  if (x >= VGA_WIDTH || y > VGA_HEIGHT)
    return -1;

  screen_row = y;
  screen_col = x;

  return 0;
}

/* ----------------------------------- */
/* Init  Functions                     */
/* ----------------------------------- */

void terminal_initialize()
{
  screen_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  screen_buff[index] = make_vgaentry(' ', screen_color);
	}
    }
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
  if (c == '\n')
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

  terminal_putentryat(c, screen_color, screen_col, screen_row);

  if ( ++screen_col == VGA_WIDTH )
    jump_line();
}


/* ----------------------------------- */
/* Recurcive Functions For Print Nb    */
/* ----------------------------------- */

void recurcive_print_int(const uint32_t i)
{
  if (i > 10)
    recurcive_print_int(i / 10);
  terminal_putchar('0' + (i % 10));
}

void recurcive_hex(uint32_t i)
{
  char base[] = "0123456789ABCDEF";

  if (i > 16)
    recurcive_hex(i / 16);
  terminal_putchar(base[i % 16]);  
}


/* ----------------------------------- */
/* Print Functions                     */
/* ----------------------------------- */

// Print Char
void putc(const char c)
{
  terminal_putchar(c);
}

// Print String
void puts(const char *data)
{
  size_t i = 0;

  if (data == NULL)
    return ;
  while (data[i] != '\0')
    terminal_putchar(data[i++]);
}

// Print Signed Int 32, 16 and 8 bits
void putd32(int32_t i)
{
  if (i < 0)
    {
      terminal_putchar('-');
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

  puts("0x");
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

  puts("0x");
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

  puts("0x");
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

int strncmp_p(char *s1, char *s2, size_t n)
{
  if (s1 == NULL || s2 == NULL || *s1 == '\0' || *s2 == '\0' || n == 0)
    return 0;

  n += 1;
  while (--n)
    {
      if (*s1 == '\0' || *s2 == '\0' || *s1 != *s2)
	return 0;
      s1++;
      s2++;
    }
  return 1;
}
  

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
	      puts(va_arg(params, char *));
	      i += 1;
	    }
	  else
	    puts("???");
	}
      else
	{
	  putc(format[i]);
	  i++;
	}
    }

  va_end(params);
}
