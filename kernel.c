#include <stdint.h>
#include <descriptor_tables/descriptor_tables.h>
#include <utils/usefull_routine.h>
#include <utils/Print.h>
#include <utils/assert.h>
#include <utils/types.h>
#include <memory/page.h>
#include <memory/kmalloc.h>

extern char end_bss;

u32     mbootstrap_kmalloc(u32 size, u32 *phys, u32 aligned);

void	*test_fill_km(int sz)
{
  int	i;
  char *p;

  p = kmalloc(sz);
  printf("km(%d) => %x\n", sz, p);
  
  for (i = 0 ; i < sz ; i++)
    p[i] = 0x41;
  return (p);
}

void	fuzzing_kmalloc_kfree()
{
  void	*tblptr[1000];
  u32	super_rand;
  u32	i;
  u32	sum;

  sum = 0;
  for (i = 0 ; i < 100 ; i++)
    {
      super_rand = ((42 << i)^(i<<(i*3))) / 3 % 300;
      tblptr[i] = kmalloc(super_rand);
      sum += super_rand;
      printf("%d: Currently allocated: %d Bytes\n", i, sum);
    }
  puts("Time to free");
  for (i = 0 ; i < 100 ; i++)
    kfree(tblptr[i]);
}

void usermode_task()
{
  int	i;

  i = 0;
  while (i < 2)
    i++;
}

void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();

  init_paging();

  puts("Coucou");
  create_process(&usermode_task);
  assert(0);

  
  puts("End");
  
  wait_until_the_end_of_your_life();
} 
