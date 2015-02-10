/*
** process.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb  9 20:34:08 2015 eax
** Last update Tue Feb 10 13:44:10 2015 eax
*/

#include <memory/page.h>
#include <memory/frame.h>
#include <utils/assert.h>
#include <utils/print.h>

#define PROCESS_STACK_START (0xE0000000)
#define PROCESS_STACK_SIZE (0x2000)

extern t_page_directory *kernel_directory;

void switch_to_user_mode(u32 addr, u32 new_esp);

void	new_stack(u32 start, u32 sz)
{
  u32	i;

  puts("Test 3");
  for(i = (u32)start; i >= ((u32)start - sz); i -= PAGE_SIZE)
    get_page(i, 1, kernel_directory);

  puts("Test 3.5");
  for(i = (u32)start; i >= ((u32)start - sz); i -= PAGE_SIZE)
    alloc_frame(get_page(i, 1, kernel_directory), 0, 1);


  enable_paging(kernel_directory);
  puts("Test 4");
}

void	create_process(void *new_eip)
{
  puts("Test 1");
  /* new_stack(PROCESS_STACK_START, PROCESS_STACK_SIZE); */


  switch_to_user_mode((u32)new_eip, PROCESS_STACK_START);
}
