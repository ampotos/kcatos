/*
** kmalloc.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Dec 25 19:50:05 2014 eax
** Last update Fri Feb 20 23:12:18 2015 eax
*/

#include <utils/print.h>
#include <utils/types.h>
#include <utils/assert.h>
#include <memory/kmalloc.h>
#include <memory/page.h>

t_heap	*kheap = NULL;
extern u32 end_bss;
/* u32 fake_heap_ptr; = (u32)&end_bss; */
u32 fake_heap_ptr;
extern t_page_directory *kernel_directory;

static u32	bootstrap_kmalloc(u32 size, u32 *phys, u32 aligned)
{
  u32	ret;

  if (aligned)
    fake_heap_ptr = (fake_heap_ptr + 0x1000) & ~(0x1000-1);
  ret = fake_heap_ptr;
  if (phys)
    *phys = ret;
  fake_heap_ptr += size;
  return (ret);
}

static void	create_header(t_km_h *p, u32 sz)
{
  p->magic = KMALLOC_MAGIC;
  p->used = 0;
  p->size = sz;
  p->next = NULL;
  p->prev = NULL;
  p->data = NULL;
}

t_heap		*new_heap(u32 start, u32 end, u8 su_lvl, u8 ro)
{
  t_heap	*heap;

  heap = (void*)bootstrap_kmalloc(sizeof(*kheap), NULL, 0);
  heap->start_addr = start;
  heap->end_addr = end;
  heap->su_lvl = su_lvl;
  heap->ro = ro;
  create_header((void*)heap->start_addr, end - start);
  return (heap);
}

static t_km_h		*split_node(t_km_h *p, u32 sz, u32 align)
{
  t_km_h	*new;

  p->data = (void*)(ALIGN_ON((u32)p + KMALLOC_HEADER_SZ, align));
  
  new = p->data + sz;
  create_header(new, p->size - (KMALLOC_HEADER_SZ + ALIGN_PTR_OFFS_ON((u32)p + KMALLOC_HEADER_SZ, align)));
  new->prev = p;
  new->next = p->next;

  p->size = KMALLOC_HEADER_SZ + ALIGN_PTR_OFFS_ON((u32)p + KMALLOC_HEADER_SZ, align) + sz;
  p->next = new;
  p->used = 1;
  
  return (p->data);
}

static void	join_node(t_km_h *p1, t_km_h *p2)
{
  p1->next = p2->next;
  if (p2->next)
    {
      p2->next->prev = p1;
    }
  p1->size += p2->size + KMALLOC_HEADER_SZ;
}

static void	*find_node(u32 sz, u32 align)
{
  t_km_h	*p;

  p = (void*)kheap->start_addr;
  while (p)
    {
      if (!p->used && p->size >= (u32)ALIGN_PTR_OFFS_ON((u32)p + KMALLOC_HEADER_SZ, align) + sz)
	return (split_node(p, sz, align));
      p = p->next;
    }
  return (NULL);
}

void		kfree(void *addr)
{
  t_km_h	*p;
  int		i;

  // The address of the node is addr - HEADER_SZ - unknown_padding_size
  p = (t_km_h*)((u32)addr - KMALLOC_HEADER_SZ);
  for (i = 0 ; i < PAGE_SIZE && ((t_km_h*)((char*)p - i))->magic != KMALLOC_MAGIC  ; i++);
  p = (t_km_h*)((char*)p - i);

  assert(p->magic == KMALLOC_MAGIC);

  p->used = 0;
  if (p->next && !p->next->used)
    join_node(p, p->next);
  if (p->prev && !p->prev->used)
    join_node(p->prev, p);
}

void	*kmalloc_all(u32 size, u32 align, u32 *phys)
{
  void	*ret;

  if (kheap)
    {
      ret = find_node(size, align);
      assertm(ret != NULL, "No more memory in kernel heap");
      if (phys)
	{
	  t_page *page = get_page((u32)ret, 0, kernel_directory);
	  *phys = page->frame * PAGE_SIZE + ((u32)ret & (PAGE_SIZE-1));
	}
    }
  else
    ret = (void*)bootstrap_kmalloc(size, phys, align == PAGE_SIZE);
  return (ret);
}

void	*kmalloc_p(u32 size, u32 *phys)
{
  return (kmalloc_all(size, sizeof(u64), phys));
}

void	*kmalloc_ap(u32 size, u32 *phys)
{
  return (kmalloc_all(size, PAGE_SIZE, phys));
}

void	*kmalloc_a(u32 size)
{
  return (kmalloc_all(size, PAGE_SIZE, NULL));
}

void	*kmalloc(u32 size)
{
  return (kmalloc_all(size, sizeof(u64), NULL));
}

void	dump_kmalloc()
{
  t_km_h	*p;

  p = (void*)kheap->start_addr;
  while (p)
    {
      int cor = 0;
      puts("================");
      if (p->magic != KMALLOC_MAGIC)
	{
	  printf("CORRUPTED NODE ! magic: %x != %x\n", p->magic, KMALLOC_MAGIC);
	  cor = 1;
	}
      printf("size:      %u\n", p->size);
      printf("addr:      %x\n", p);
      printf("data addr: %x\n", p->data);
      printf("next:      %x\n", p->next);
      printf("prev:      %x\n", p->prev);
      printf("used:      %d\n", p->used);
      p = p->next;
      if (cor)
	p = NULL;
    }
}
