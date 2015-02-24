#include <descriptor_tables/descriptor_tables.h>
#include <descriptor_tables/pic/pic.h>
#include <utils/usefull_routine.h>
#include <utils/print.h>
#include <utils/assert.h>
#include <utils/types.h>
#include <memory/page.h>
#include <memory/kmalloc.h>
#include <syscall/syscall.h>
#include <process/process.h>
#include <multiboot.h>
#include <initrd/initrd.h>
#include <kmodule/kmodule.h>

extern u32 fake_heap_ptr;

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

void kernel_main(u32 magic, t_multiboot *multiboot)
{
  t_initrd	*ird;
  
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();
  
  assertm(multiboot->mods_count != 0, "You didn't launch the kernel with the initrd. try: make run");
  
  fake_heap_ptr = *(u32*)(multiboot->mods_addr + 4);
  init_paging();

  asm volatile ("sti");
  setup_pit(1000);
  
  assert(multiboot->mods_count != 0);
  ird = load_initrd(*(u32*)(multiboot->mods_addr));
  kmodule_load(ird->kmods);
} 
