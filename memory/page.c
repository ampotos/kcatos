/*
** page.c for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Dec 27 15:20:28 2014 eax
** Last update Sun Dec 28 15:03:33 2014 eax
*/

#include <memory/page.h>
#include <utils/string.h>
#include <memory/kmalloc.h>

t_page_directory *kernel_directory;
extern u32 fake_heap_ptr;

void	init_paging()
{
  u32	i;
  u32 frm_idx;
  kernel_directory = (void *)bootstrap_kmalloc(sizeof(t_page_directory), NULL, 1);
  memset((u32)kernel_directory, 0, sizeof(t_page_directory));

  i = 0;
  frm_idx = 0;
  while (i < fake_heap_ptr)
    {
      u32 tmp;
      u32 table_idx = i / 0x1000 / 1024;
      if (!kernel_directory->tables[table_idx])
	{
	  kernel_directory->tables[table_idx] = (t_page_table*)bootstrap_kmalloc(sizeof (t_page_table), &tmp, 1);
	  memset((u32)kernel_directory->tables[table_idx], 0, 0x1000);
	  kernel_directory->tables_phys[table_idx] = tmp | 0x7;
	}
      kernel_directory->tables[table_idx]->pages[i/0x1000%1024].p = 1;
      kernel_directory->tables[table_idx]->pages[i/0x1000%1024].rw = 1;
      kernel_directory->tables[table_idx]->pages[i/0x1000%1024].us = 1;
      kernel_directory->tables[table_idx]->pages[i/0x1000%1024].frame = frm_idx++;
      i +=0x1000;
    }
  /* wait_until_the_end_of_your_life(); */
  asm volatile("mov %0, %%cr3":: "r"(&kernel_directory->tables_phys ));
  u32 cr0;
  asm volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0":: "r"(cr0));
}
