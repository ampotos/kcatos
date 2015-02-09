/*
** page.c for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Dec 27 15:20:28 2014 eax
** Last update Mon Feb  9 22:35:31 2015 eax
*/

#include <memory/page.h>
#include <utils/string.h>
#include <utils/assert.h>
#include <memory/kmalloc.h>
#include <memory/frame.h>

t_page_directory *kernel_directory;
extern u32 fake_heap_ptr;
extern t_heap *kheap;

t_page	*get_page(u32 addr, int create, t_page_directory *dir)
{
  addr /= PAGE_SIZE;
  u32 table_idx = addr / PAGE_TABLE_NB;
  u32 phys;
  
  assert(table_idx < PAGE_TABLE_NB);
  if (!dir->tables[table_idx] && create)
    {
      dir->tables[table_idx] = (t_page_table*)kmalloc_ap(sizeof (t_page_table), &phys);
      memset((u32)dir->tables[table_idx], 0, 0x1000);
      dir->tables_phys[table_idx] = phys | 0x7;
    }
  else if (create == 0)
    return (0);
  
  return (dir->tables[table_idx]->pages + (addr % PAGE_TABLE_NB));
}

void	enable_paging(t_page_directory *dir)
{
  u32	cr0;

  //TODO: write this routine in asm
  
  asm volatile("mov %0, %%cr3":: "r"(&dir->tables_phys));
  asm volatile("mov %%cr0, %0": "=r"(cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0":: "r"(cr0));
  
}

void	init_paging()
{
  u32	i;
 
  init_frame();
  kernel_directory = (void *)kmalloc_a(sizeof(t_page_directory));
  memset((u32)kernel_directory, 0, sizeof(t_page_directory));

  for (i = KHEAP_START ; i < KHEAP_START + KHEAP_INITIAL_SIZE ; i += PAGE_SIZE)
    get_page(i, 1, kernel_directory);

  for(i = (u32)0xE0000000; i >= ((u32)0xE0000000 - 0x2000); i -= PAGE_SIZE)
    get_page(i, 1, kernel_directory);

  for (i = 0 ; i < fake_heap_ptr + PAGE_SIZE ; i += PAGE_SIZE)
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

  for (i = KHEAP_START ; i < KHEAP_START + KHEAP_INITIAL_SIZE ; i += PAGE_SIZE)
    alloc_frame(get_page(i, 1, kernel_directory), 0, 0);

  for(i = (u32)0xE0000000; i >= ((u32)0xE0000000 - 0x2000); i -= PAGE_SIZE)
    alloc_frame(get_page(i, 1, kernel_directory), 0, 1);

   enable_paging(kernel_directory);
   kheap = new_heap(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0, 0);
}
