#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables/descriptor_tables.h"
#include "Print.h"

/* Hardware text mode color constants. */

size_t strlen(const char* str)
{
  size_t ret = 0;
  while ( str[ret] != 0 )
    ret++;
  return ret;
}

void terminal_writestring(const char* data)
{
  size_t datalen = strlen(data);
  for ( size_t i = 0; i < datalen; i++ )
    terminal_putchar(data[i]);
}

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  terminal_setcolor(make_color(COLOR_BLACK, COLOR_WHITE));
  puts("I'm alive");
  putc('\n');
  putd32(-123456789);
  putc('\n');
  putd16(-12345);
  putc('\n');
  putd8(-123);
  putc('\n');
  putu32(123456789);
  putc('\n');
  putu16(12345);
  putc('\n');
  putu8(123);
  putc('\n');
  puth32(123456789);
  putc('\n');
  puth16(12345);
  putc('\n');
  puth8(123);
  puts("\na\nb\nc\nd\ne\nf\ng\nh\ni\nj\nk\nl\nm\nn\no\np\nq\nr\n");

  printf("Test Signed Int : %32d, %16d, %8d\n", -123456789, -12345, -123);
  printf("Test Unsigned Int : %32u, %16u, %8u\n", 123456789, 12345, 123);
  printf("Test Unsigned Int Hex : %32h, %16h, %8h\n", 123456789, 240, 255);
  printf("Test String : \"%s\"\n", "String");
  printf("Test Char : '%c'\n", 'c');
  printf("Test Unknow : %a\n");
  printf("Test Percent : %%\n");

  //  init_descriptor_tables();
  while (1)
    {      
    }
} 
