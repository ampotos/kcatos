/*
** syscall_handler.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 00:03:33 2015 eax
** Last update Tue Mar  3 15:40:10 2015 
*/

#include <utils/print.h>
#include <syscall/syscall_handler.h>
#include <utils/usefull_routine.h>
#include <memory/kmalloc.h>
#include <syscall/syscall.h>
#include <descriptor_tables/pic/keyboard.h>
#include <syscall/read.h>

#define puts_screen puts

u32	sbrk(u32);

static void *syscalls[] =
  {
    wait_until_the_end_of_your_life,
    write_screen,
    puts_screen,
    is_computer_on,
    is_computer_on_fire,
    print_logo,
    sbrk,
    kpause,
    read,
    read_non_block
  };

u32	sbrk(u32 incr)
{
  return (UHEAP_START);
}

void	syscall_handler(regs_t *regs)
{
  if (regs->eax > sizeof(syscalls) / sizeof(*syscalls))
    return;

  void	*scall = syscalls[regs->eax];
  regs->eax = syscall_do_call((u32)scall, regs->edi, regs->esi, regs->edx, regs->ecx, regs->ebx);
}
