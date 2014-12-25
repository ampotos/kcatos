#include <stddef.h>
#include <stdint.h>
#include <descriptor_tables/descriptor_tables.h>
#include <utils/usefull_routine.h>
#include <utils/Print.h>
#include <utils/assert.h>

extern char end_bss;

void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();
  /* asm volatile("int $0x3"); */

  printf("end_bss: %32h\n", &end_bss);
  assert(1 == 1);
  assert(1 == 2);
  wait_until_the_end_of_your_life();
} 
