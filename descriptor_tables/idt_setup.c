/*
** idt_setup.c for KCatos in /home/ampotos/kcatos/interrupt_table
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 17:29:52 2014 
** Last update Wed Dec 24 15:44:01 2014 eax
*/

#include "idt.h"
#include <utils/string.h>

static	t_idt_entry	idt[256];
static	t_idt_ptr	idt_ptr;


// when user alnd exist change DPL from 0 to 3


void	idt_set_entry(uint8_t num, uint32_t base)
{
  idt[num].base_lo = base & 0xFFFF;
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = 0x08;
  idt[num].always0 = 0;
  idt[num].magic = 14;
  idt[num].dpl = 0;
  idt[num].p = 1;
}

void	setup_idt()
{
  idt_ptr.limit = sizeof(t_idt_entry) * 256 - 1;
  idt_ptr.base = (uint32_t)(&idt);

  bzero((uint32_t)idt, sizeof(t_idt_entry) * 255);

  idt_set_entry(0, (uint32_t)interrupt0);
  idt_set_entry(1, (uint32_t)interrupt1);
  idt_set_entry(2, (uint32_t)interrupt2);
  idt_set_entry(3, (uint32_t)interrupt3);
  idt_set_entry(4, (uint32_t)interrupt4);
  idt_set_entry(5, (uint32_t)interrupt5);
  idt_set_entry(6, (uint32_t)interrupt6);
  idt_set_entry(7, (uint32_t)interrupt7);
  idt_set_entry(8, (uint32_t)interrupt8);
  idt_set_entry(9, (uint32_t)interrupt9);
  idt_set_entry(10, (uint32_t)interrupt10);
  idt_set_entry(11, (uint32_t)interrupt11);
  idt_set_entry(12, (uint32_t)interrupt12);
  idt_set_entry(13, (uint32_t)interrupt13);
  idt_set_entry(14, (uint32_t)interrupt14);
  idt_set_entry(15, (uint32_t)interrupt15);
  idt_set_entry(16, (uint32_t)interrupt16);
  idt_set_entry(17, (uint32_t)interrupt17);
  idt_set_entry(18, (uint32_t)interrupt18);
  idt_set_entry(19, (uint32_t)interrupt19);
  idt_set_entry(20, (uint32_t)interrupt20);
  idt_set_entry(21, (uint32_t)interrupt21);
  idt_set_entry(22, (uint32_t)interrupt22);
  idt_set_entry(23, (uint32_t)interrupt23);
  idt_set_entry(24, (uint32_t)interrupt24);
  idt_set_entry(25, (uint32_t)interrupt25);
  idt_set_entry(26, (uint32_t)interrupt26);
  idt_set_entry(27, (uint32_t)interrupt27);
  idt_set_entry(28, (uint32_t)interrupt28);
  idt_set_entry(29, (uint32_t)interrupt29);
  idt_set_entry(30, (uint32_t)interrupt30);
  idt_set_entry(31, (uint32_t)interrupt31);

  idt_load((uint32_t)&idt_ptr);
}
