/*
** kmalloc.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Dec 25 19:50:05 2014 eax
** Last update Sun Dec 28 15:05:58 2014 eax
*/

#include <utils/types.h>
#include <memory/kmalloc.h>

extern u32 end_bss;
u32 fake_heap_ptr = (u32)&end_bss;

u32	bootstrap_kmalloc(u32 size, u32 *phys, u32 aligned)
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
