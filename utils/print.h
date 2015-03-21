#ifndef PRINT_H_
#define PRINT_H_

#include <utils/types.h>
#include <stdarg.h>
#include <descriptor_tables/idt.h>

#include <utils/string.h>

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

void terminal_putchar(char c);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_initialize();
uint16_t make_vgaentry(char c, uint8_t color);

// color
void terminal_setcolor(uint8_t color);
void terminal_fg_setcolor(enum vga_color fg);
void terminal_bg_setcolor(enum vga_color bg);
uint8_t make_color(enum vga_color fg, enum vga_color bg);

// set pos return -1 on error else retrun 0
int terminal_setpos(size_t x, size_t y);
void terminal_getpos(size_t *x, size_t *y);
uint16_t get_cur_entry();
enum vga_color terminal_fg_getcolor();
enum vga_color terminal_bg_getcolor();
 
// Print Char
void putc(char c);

// Print String
u32 puts(const char *data);
u32 puts_nolf(const char *data);

// Print Signed Int 32, 16 and 8 bits
void putd32(int32_t i);
void putd16(int16_t i);
void putd8(int8_t i);

// Print Unsigned Int 32, 16 and 8 bits
void putu32(uint32_t i);
void putu16(uint16_t i);
void putu8(uint8_t i);

// Print Unsigned Int in Hex 32, 16 and 8 bits
void puth32(uint32_t i);
void puth16(uint16_t i);
void puth8(uint8_t i);

// Prinf tags : 32d, 16d, 8d, 32u, 16u, 8u, 32h, 16h, 8h, c, s
void printf(char *, ...);

// Clean
void clean();


void	panic_print(regs_t reg);
void	panic_print_assert(char *filename, int linenum, char *expr, char *msg);
size_t	write_screen(char *data, size_t sz);
u32	print_logo();

int    draw_window(char *title, size_t pos_x, size_t pos_y, size_t width, size_t height, enum vga_color fg, enum vga_color bg);

#endif /* PRINT_H_ */
