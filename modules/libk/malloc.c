/*
** malloc.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 13 22:42:00 2015 eax
** Last update Wed Feb 25 08:24:05 2015 eax
*/

#include "types.h"
#include "malloc.h"

static t_malloc	malloc_data = {0,0,0};

static void	create_header(t_m_h *p, u32 sz)
{
  p->magic = MALLOC_MAGIC;
  p->used = 0;
  p->size = sz;
  p->next = NULL;
  p->prev = NULL;
  p->data = NULL;
}

static t_m_h		*split_node(t_m_h *p, u32 sz, u32 align)
{
  t_m_h	*new;

  p->data = (void*)(ALIGN_ON((u32)p + MALLOC_HEADER_SZ, align));
  
  new = p->data + sz;
  create_header(new, p->size - (MALLOC_HEADER_SZ + ALIGN_PTR_OFFS_ON((u32)p + MALLOC_HEADER_SZ, align)));
  new->prev = p;
  new->next = p->next;

  p->size = MALLOC_HEADER_SZ + ALIGN_PTR_OFFS_ON((u32)p + MALLOC_HEADER_SZ, align) + sz;
  p->next = new;
  p->used = 1;
  
  return (p->data);
}

static void	join_node(t_m_h *p1, t_m_h *p2)
{
  p1->next = p2->next;
  if (p2->next)
    {
      p2->next->prev = p1;
    }
  p1->size += p2->size + MALLOC_HEADER_SZ;
}

static void	*find_node(u32 sz, u32 align)
{
  t_m_h	*p;

  p = (void*)malloc_data.start_addr;
  while (p)
    {
      if (!p->used && p->size >= (u32)ALIGN_PTR_OFFS_ON((u32)p + MALLOC_HEADER_SZ, align) + sz)
	return (split_node(p, sz, align));
      p = p->next;
    }
  return (NULL);
}

void		free(void *addr)
{
  t_m_h	*p;
  int		i;

  // The address of the node is addr - HEADER_SZ - unknown_padding_size
  p = (t_m_h*)((u32)addr - MALLOC_HEADER_SZ);
  for (i = 0 ; i < PAGE_SIZE && ((t_m_h*)((char*)p - i))->magic != MALLOC_MAGIC  ; i++);
  p = (t_m_h*)((char*)p - i);

  /* assert(p->magic == MALLOC_MAGIC); */

  p->used = 0;
  if (p->next && !p->next->used)
    join_node(p, p->next);
  if (p->prev && !p->prev->used)
    join_node(p->prev, p);
}

static void	init_malloc()
{
  /* malloc_data.start_addr = syscall_sbrk(0); */
  malloc_data.start_addr = 0xf0000000;
  malloc_data.end_addr = malloc_data.start_addr + PAGE_SIZE;
  malloc_data.init = 1;
}

void	*malloc_all(u32 size, u32 align)
{
  void	*ret;

  if (!malloc_data.init)
    init_malloc();
  ret = find_node(size, align);
  /* assertm(ret != NULL, "No more memory in kernel heap"); */
  return (ret);
}

void	*malloc_a(u32 size)
{
  return (malloc_all(size, PAGE_SIZE));
}

void	*malloc(u32 size)
{
  return (malloc_all(size, sizeof(u64)));
}

/* void	dump_malloc() */
/* { */
/*   t_m_h	*p; */

/*   p = (void*)malloc_data.start_addr; */
/*   while (p) */
/*     { */
/*       int cor = 0; */
/*       puts("================"); */
/*       if (p->magic != MALLOC_MAGIC) */
/* 	{ */
/* 	  printf("CORRUPTED NODE ! magic: %x != %x\n", p->magic, MALLOC_MAGIC); */
/* 	  cor = 1; */
/* 	} */
/*       printf("size:      %u\n", p->size); */
/*       printf("addr:      %x\n", p); */
/*       printf("data addr: %x\n", p->data); */
/*       printf("next:      %x\n", p->next); */
/*       printf("prev:      %x\n", p->prev); */
/*       printf("used:      %d\n", p->used); */
/*       p = p->next; */
/*       if (cor) */
/* 	p = NULL; */
/*     } */
/* } */
