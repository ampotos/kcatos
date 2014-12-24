#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables/descriptor_tables.h"
#include "utils/Print.h"

void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();
  asm volatile("int $0x3");
  while (1)
    {      
    }
} 
