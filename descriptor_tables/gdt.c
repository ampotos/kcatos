/*
** gdt.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Dec  2 22:55:52 2014 eax
** Last update Tue Feb 24 14:58:25 2015 
*/

#include <descriptor_tables/gdt.h>
#include <utils/string.h>
#include <utils/assert.h>

static t_tss_entry	tss_entry;
static t_gdt_entry	gdt_entries[6];
static t_gdt_ptr	gdt_ptr;

static void set_gdt_entrie(uint8_t idx,  uint32_t base, uint32_t limit, uint16_t flags)
{
  gdt_entries[idx].limit_low = limit & 0xFFFF;
  gdt_entries[idx].base_low = base & 0xFFFF;
  gdt_entries[idx].base_middle = (base >> 16) & 0xFF;
  gdt_entries[idx].code |= ((flags & CODE) != 0);
  gdt_entries[idx].expand_down |= ((flags & EXPAND_DOWN) != 0);
  gdt_entries[idx].read |= ((flags & READ) != 0);
  gdt_entries[idx].s = (flags & CODE_DATA) != 0;
  gdt_entries[idx].dpl = flags & 0x3;
  gdt_entries[idx].p = 1;
  gdt_entries[idx].limit_high = (limit >> 16) & 0xF;
  gdt_entries[idx].avl = 0;
  gdt_entries[idx].l = (flags & MODE_64B) != 0;
  gdt_entries[idx].db = (flags & OP_SIZE_32B) != 0;
  gdt_entries[idx].g = (flags & GRANUL_1K) != 0;
  gdt_entries[idx].base_high = (base >> 24) & 0xFF;
}

static void write_tss(u32 idx, u16 ss0, s32 esp0)
{
  u32 base = (u32)&tss_entry;
  u32 limit = base + sizeof(tss_entry);
  set_gdt_entrie(idx, base, limit,
  		 RING(3) | SYSTEM | CODE);

  gdt_entries[idx].accessed = 1;

  bzero((u32)&tss_entry, sizeof (tss_entry));
    
  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;

  tss_entry.cs = 0x08 | 0x3;
  tss_entry.ss = 0x10 | 0x3;
  tss_entry.ds = 0x10 | 0x3;
  tss_entry.es = 0x10 | 0x3;
  tss_entry.fs = 0x10 | 0x3;
  tss_entry.gs = 0x10 | 0x3;
}


void init_gdt()
{
  gdt_ptr.base = (uint32_t)&gdt_entries;
  gdt_ptr.limit = (sizeof (t_gdt_entry) * 6) - 1;

  set_gdt_entrie(0, 0, 0, 0);
  set_gdt_entrie(1, 0, 0xFFFFFFFF, RING(0) | CODE_DATA | CODE | READ | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(2, 0, 0xFFFFFFFF, RING(0) | CODE_DATA | DATA | WRITE | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(3, 0, 0xFFFFFFFF, RING(3) | CODE_DATA | CODE | READ | OP_SIZE_32B | GRANUL_1K);
  set_gdt_entrie(4, 0, 0xFFFFFFFF, RING(3) | CODE_DATA | DATA | WRITE | OP_SIZE_32B | GRANUL_1K);

  u32 esp;
  asm volatile("mov %%esp, %0": "=r"(esp)); // TODO: This is a temporary hack.
  
  write_tss(5, 0x10, esp);
  gdt_flush((uint32_t)&gdt_ptr);
  tss_flush();
}
