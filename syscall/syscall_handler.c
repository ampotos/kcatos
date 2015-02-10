/*
** syscall_handler.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 00:03:33 2015 eax
** Last update Tue Feb 10 02:33:46 2015 eax
*/

#include <utils/Print.h>
#include <syscall/syscall_handler.h>
#include <utils/usefull_routine.h>

#define puts_screen puts

static void *syscalls[] =
  {
    wait_until_the_end_of_your_life,
    write_screen,
    puts_screen
  };

void	syscall_handler(regs_t *regs)
{
  printf("regs->eax: %d\n", regs->eax);
  
  if (regs->eax > sizeof(syscalls) / sizeof(*syscalls))
    return;

  void	*scall = syscalls[regs->eax];
  
  int ret;
  asm volatile (" \
     push %1; \
     push %2; \
     push %3; \
     push %4; \
     push %5; \
     call *%6; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
     pop %%ebx; \
   " : "=a" (ret) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (scall));
  regs->eax = ret;
}
