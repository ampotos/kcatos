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
}

void kernel_main(u32 magic, t_multiboot *multiboot)
{
  t_initrd	*ird;
  t_elfparse	ep;
  int		ret;
  
  terminal_initialize();
  terminal_setpos(0, 0);

  init_descriptor_tables();

  assertm(multiboot->mods_count != 0, "You didn't launch the kernel with the initrd. try: make run");
  assertm(multiboot->num != 0, "You didn't run the grub version. So the elf wasn't present. Bye");
  
  fake_heap_ptr = *(u32*)(multiboot->mods_addr + 4);
  init_paging();

  ret = kern_parse(multiboot, &ep);
  assertm(ret != -1, "Fail loading elf kernel");
    
  asm volatile ("sti");
  setup_pit(1000);
  ird = load_initrd(*(u32*)(multiboot->mods_addr));

  /* while (keyboard_getchar() != 0xff); */
  keyboard_clear_buff(1024); // size of read buff  == 1024
  
  /* kmodule_load_all(ird->kmods, &ep.symb); */
  kmodule_load_by_name("libk.kso", ird->kmods, &ep.symb);
  kmodule_load_by_name("t2.kso", ird->kmods, &ep.symb);
  kmodule_load_by_name("intro.kso", ird->kmods, &ep.symb);
  kmodule_exec_by_name("intro.kso", ird->kmods, KMODULE_EXEC_KERNELLAND);
  /* kmodule_exec_by_name("t2.kso", ird->kmods, KMODULE_EXEC_USERLAND); */
  /* launch_task(ird); */
} 
