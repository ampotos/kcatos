/*
** gdt.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Dec  2 21:13:49 2014 eax
** Last update Tue Feb 10 13:42:05 2015 eax
*/

#ifndef GDT_H_
#define GDT_H_

#include <utils/types.h>

#define RING(n) (n & 0x03)
#define CODE_DATA (4)
#define SYSTEM (0)
#define GRANUL_1K (8)
#define MODE_64B (16)
#define CODE (32)
#define DATA (0)
#define READ (64)
#define WRITE (64) /* This is not a bug */
#define EXPAND_DOWN (128)
#define CONFORMING (128) /* This is not a bug */
#define OP_SIZE_32B (256)

/*
** Global descriptor entry
** http://download.intel.com/design/processor/manuals/253668.pdf # 3.4.5 Segment Descriptors
*/

typedef struct s_gdt_entry
{
  u16      limit_low;      /* limit[0:16] */
  u16      base_low;       /* base[0:16] */
  u8       base_middle;    /* base[16:24] */

  u8	   accessed:1;
  u8	   read:1;
  u8	   expand_down:1;
  u8	   code:1;
  u8       s:1;            /* Descriptor type (0 = system ; 1 = code or data) */
  u8       dpl:2;          /* Descriptor privilege level (ring 0-3) */
  u8       p:1;            /* Segment present */
  
  u8       limit_high:4;   /* limit[16:20] */
  u8       avl:1;          /* Available for use by system software */
  u8       l:1;            /* 64b mode segment (ia-32 mode only) */
  u8       db:1;           /* Default operation size (0 = 16b segment ; 1 = 32b segment) */
  u8       g:1;            /* Granularity (0 = 1b ; 1 = 1024b) */
  u8       base_high;      /* base[24:31] */
}  __attribute__((packed)) t_gdt_entry;


typedef struct s_gdt_ptr
{
  u16	limit;
  u32	base;
} __attribute__((packed)) t_gdt_ptr;


typedef struct s_tss_entry
{
  u32 prev_tss;
  u32 esp0;
  u32 ss0;
  u32 esp1;
  u32 ss1;
  u32 esp2;
  u32 ss2;
  u32 cr3;
  u32 eip;
  u32 eflags;
  u32 eax;
  u32 ecx;
  u32 edx;
  u32 ebx;
  u32 esp;
  u32 ebp;
  u32 esi;
  u32 edi;
  u32 es;
  u32 cs;
  u32 ss;
  u32 ds;
  u32 fs;
  u32 gs;
  u32 ldt;
  u16 trap;
  u16 iomap_base;
} __attribute__((packed)) t_tss_entry;


void gdt_flush(u32 gdt_addr);
void tss_flush();
void init_gdt();

#endif
