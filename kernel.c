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
#include <elf/elf_internal.h>
#include <descriptor_tables/pic/keyboard.h>
extern u32 fake_heap_ptr;

void	launch_task(t_initrd *ird)
{
  kmodule_exec_by_name("intro.kso", ird->kmods, KMODULE_EXEC_USERLAND);
  kmodule_exec_by_name("shell.kso", ird->kmods, KMODULE_EXEC_USERLAND);
}

void kernel_main(u32 magic, t_multiboot *multiboot)
{
  t_initrd	*ird;
  t_elfparse	ep;
  int		ret;

  terminal_initialize();
  terminal_setpos(0, 0);
  puts("[-] Initalization of terminal: Ok");

  init_descriptor_tables();  

  assertm(magic == 0x2badb002, "The multiboot magic isn't correct.");
  assertm(multiboot->mods_count != 0, "You didn't launch the kernel with the initrd. try: make run-iso");
  assertm(multiboot->num != 0, "You didn't run the grub version. Therefore we can't load the modules. Try: make run-iso");
  
  fake_heap_ptr = *(u32*)(multiboot->mods_addr + 4);
  printf("[-] Initalization of terminal:");
  init_paging();
  puts(" Ok");
  
  ret = kern_parse(multiboot, &ep);
  assertm(ret != -1, "Fail loading elf kernel");

  printf("[-] Initalization of terminal:");
  asm volatile ("sti");
  setup_pit(1000);
  puts(" Ok");
  ird = load_initrd(*(u32*)(multiboot->mods_addr));

  unsigned i;
  i = 0;
  while (i < 429496529)
    i++;
  
  while (keyboard_getchar() != 0xff);

  printf("[-] Loading of modules:");
  kmodule_load_all(ird->kmods, &ep.symb);
  puts(" Ok");
  launch_task(ird);
} 
