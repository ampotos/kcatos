/*
** kmalloc.h for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Dec 28 13:38:10 2014 eax
** Last update Mon Feb  9 00:06:56 2015 eax
*/

#ifndef KMALLOC_H_
#define KMALLOC_H_

#include <utils/types.h>

#define KMALLOC_MAGIC (0xabcdead)
#define KMALLOC_HEADER_SZ (sizeof (t_kmalloc_header))
#define KHEAP_START (0xC0000000)
#define KHEAP_INITIAL_SIZE (0x100000)

#define ALIGN_ON(x,n) (size_t)((~(n-1))&(((u64)x)+(n-1)))
#define ALIGN_PTR(x) (u32)(ALIGN_ON((x), sizeof(u64)))
#define ALIGN_PTR_OFFS(x) ((u64)(ALIGN_PTR(x)) - (u64)(x))

typedef struct s_kmalloc_header
{
  u32				magic:31;
  u32				used:1;
  u32				size;
  struct s_kmalloc_header	*next;
  struct s_kmalloc_header	*prev;
  void				*data;
}				t_kmalloc_header;

typedef t_kmalloc_header t_km_h;

typedef struct
{
  u32	start_addr;
  u32	end_addr;
  u8	su_lvl;
  u8	ro;
} t_heap;

u32	bootstrap_kmalloc(u32 size, u32 *phys, u32 aligned);
t_heap	*new_heap(u32 start, u32 end, u8 su_lvl, u8 ro);
void	*kmalloc(u32 size);
void	kfree(void *addr);
void	dump_kmalloc();
#endif
