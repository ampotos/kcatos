/*
** kmalloc.h<libk> for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 13 22:48:05 2015 eax
** Last update Wed Feb 25 08:00:29 2015 eax
*/

#ifndef MALLOC_H_
#define MALLOC_H_

#include "types.h"

#define PAGE_SIZE (0x1000)
#define MALLOC_MAGIC (0xabcdead)
#define MALLOC_HEADER_SZ (sizeof (t_malloc_header))


#define ALIGN_ON(x,n) (size_t)((~(n-1))&(((u64)x)+(n-1)))
#define ALIGN_PTR(x) (u32)(ALIGN_ON((x), sizeof(u64)))
#define ALIGN_PTR_OFFS_ON(x,n) ((u64)(ALIGN_ON((x),(n))) - (u64)(x))
#define ALIGN_PTR_OFFS(x) (ALIGN_PTR_OFFS_ON(x, sizeof(u64)))

typedef struct s_malloc_header
{
  u32				magic:31;
  u32				used:1;
  u32				size;
  struct s_malloc_header	*next;
  struct s_malloc_header	*prev;
  void				*data;
}				t_malloc_header;

typedef t_malloc_header t_m_h;

typedef struct
{
  u32	start_addr;
  u32	end_addr;
  u32	init;
} t_malloc;

void	*malloc(u32 size);
void	*malloc_a(u32 size);
void	free(void *addr);
void	dump_malloc();
#endif
