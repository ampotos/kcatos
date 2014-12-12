#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "descriptor_tables/descriptor_tables.h"
#include "utils/Print.h"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
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
