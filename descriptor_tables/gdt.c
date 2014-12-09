/*
** gdt.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Dec  2 22:55:52 2014 eax
** Last update Mon Dec  8 18:29:35 2014 
*/

#include "gdt.h"

static t_gdt_entry	gdt_entries[5];
static t_gdt_ptr	gdt_ptr;

static void set_gdt_entrie(uint8_t idx,  uint32_t base, uint32_t limit, uint16_t flags)
{
  /* TODO: check/assert vulues */
  gdt_entries[idx].limit_low = limit & 0xFFFF;
  gdt_entries[idx].base_low = base & 0xFFFF;
  gdt_entries[idx].base_middle = (base >> 16) & 0xFFFF;
  gdt_entries[idx].type |= ((flags & CODE) != 0) << 3;
  gdt_entries[idx].type |= ((flags & EXPAND_DOWN) != 0) << 2;
  gdt_entries[idx].type |= ((flags & READ) != 0) << 1;
  gdt_entries[idx].s = (flags & CODE_DATA) != 0;
  gdt_entries[idx].dpl = flags & 0x3;
  gdt_entries[idx].p = 1;
  gdt_entries[idx].limit_high = (limit >> 16) & 0xFFFF;
  gdt_entries[idx].avl = 0;
  gdt_entries[idx].l = (flags & MODE_64B) != 0;
  gdt_entries[idx].db = (flags & OP_SIZE_32B) != 0;
  gdt_entries[idx].g = (flags & GRANUL_1K) != 0;
  gdt_entries[idx].base_high = (base >> 24) & 0xFFFF;
}

void init_gdt()
{
  gdt_ptr.base = (uint32_t)&gdt_entries;
  gdt_ptr.limit = (sizeof (*gdt_entries) * 5) - 1;

  set_gdt_entrie(0, 0, 0, 0);
  set_gdt_entrie(1, 0, 0xFFFFFFFF, RING(0) | CODE_DATA | CODE | READ | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(2, 0, 0xFFFFFFFF, RING(0) | CODE_DATA | DATA | WRITE | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(3, 0, 0xFFFFFFFF, RING(3) | CODE_DATA | CODE | READ | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(4, 0, 0xFFFFFFFF, RING(3) | CODE_DATA | DATA | WRITE | OP_SIZE_32B | GRANUL_1K);

  gdt_flush((uint32_t)&gdt_ptr);
}
