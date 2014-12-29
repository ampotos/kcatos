#include <stdint.h>
#include <descriptor_tables/descriptor_tables.h>
#include <utils/usefull_routine.h>
#include <utils/Print.h>
#include <utils/assert.h>
#include <utils/types.h>
#include <memory/page.h>

extern char end_bss;

u32     mbootstrap_kmalloc(u32 size, u32 *phys, u32 aligned);

void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();
  /* asm volatile("int $0x3"); */

  
  init_paging();

  puts("Hi. Paging is now enabled.\n");
  puts("Let's read some junk address now...\n\n");
  /* u32	*p; */
  /* p = (u32*)0xFFFFFF; */
  /* *p = 42; */
  
  wait_until_the_end_of_your_life();
} 
