#include <descriptor_tables/descriptor_tables.h>
#include <utils/usefull_routine.h>
#include <utils/print.h>
#include <utils/assert.h>
#include <utils/types.h>
#include <memory/page.h>
#include <memory/kmalloc.h>
#include <syscall/syscall.h>
#include <process/process.h>
#include <libk/malloc.h>

void usermode_task_useless()
{
  if (!syscall_is_computer_on())
    if (syscall_is_computer_on_fire())
      {
        syscall_puts_screen("Oh sheat! Fire! Fire! Fire!");
	syscall_puts_screen("Lets get out of there!");
	*((u32*)usermode_task_useless) /= ((u32)usermode_task_useless)&0;
      }

  syscall_puts_screen("Hi. This is KCatOs. Deal with it.");
  syscall_oh_crap();
  syscall_wait_until_the_end_of_your_life();
}

void	usermode_task_usefull()
{
  int	*p;

  /* p = malloc(4); */
  /* *p = 42; */
  /* syscall_puts_screen("Nice, userland malloc"); */
  printf("tests %d\n", 42);
  syscall_wait_until_the_end_of_your_life();
}

void kernel_main()
{
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();
  init_paging();


  create_process(&usermode_task_usefull);
  /* assertm(0, "After create process. Should not happen."); */
  
  wait_until_the_end_of_your_life();
} 
