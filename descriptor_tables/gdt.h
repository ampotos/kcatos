/*
** gdt.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Dec  2 21:13:49 2014 eax
** Last update Wed Dec 24 14:37:15 2014 eax
*/

#ifndef GDT_H_
#define GDT_H_

#include <stdint.h>

#define RING(n) (n & 0x03)
#define CODE_DATA (4)
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
  uint16_t      limit_low;      /* limit[0:16] */
  uint16_t      base_low;       /* base[0:16] */
  uint8_t       base_middle;    /* base[16:24] */
  uint8_t       type:4;         /* Segment type */
  uint8_t       s:1;            /* Descriptor type (0 = system ; 1 = code or data) */
  uint8_t       dpl:2;          /* Descriptor privilege level (ring 0-3) */
  uint8_t       p:1;            /* Segment present */
  uint8_t       limit_high:4;   /* limit[16:20] */
  uint8_t       avl:1;          /* Available for use by system software */
  uint8_t       l:1;            /* 64b mode segment (ia-32 mode only) */
  uint8_t       db:1;           /* Default operation size (0 = 16b segment ; 1 = 32b segment) */
  uint8_t       g:1;            /* Granularity (0 = 1b ; 1 = 1024b) */
  uint8_t       base_high;      /* base[24:31] */
}  __attribute__((packed)) t_gdt_entry;


typedef struct s_gdt_ptr
{
  uint16_t	limit;
  uint32_t	base;
} __attribute__((packed)) t_gdt_ptr;

void gdt_flush(uint32_t gdt_addr);
void init_gdt();

#endif
