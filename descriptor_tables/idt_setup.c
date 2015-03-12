/*
** idt_setup.c for KCatos in /home/ampotos/kcatos/interrupt_table
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 17:29:52 2014 
** Last update Tue Mar 10 11:19:47 2015 eax
*/

#include <descriptor_tables/idt.h>
#include <utils/string.h>
#include <utils/assert.h>
#include <syscall/syscall_handler.h>
#include <descriptor_tables/pic/pic.h>

static	t_idt_entry	idt[256];
static	t_idt_ptr	idt_ptr;


// when user alnd exist change DPL from 0 to 3


void	idt_set_entry(uint8_t num, uint8_t dpl, uint32_t base)
{
  idt[num].base_lo = base & 0xFFFF;
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = 0x08;
  idt[num].always0 = 0;
  idt[num].magic = 14;
  idt[num].dpl = dpl & 3;
  idt[num].p = 1;
}

void	setup_idt()
{
  idt_ptr.limit = sizeof(t_idt_entry) * 256 - 1;
  idt_ptr.base = (uint32_t)(&idt);

  bzero((uint32_t)idt, sizeof(t_idt_entry) * 255);
  printf("[-] Initalization of irq:");
  init_irq();
  puts(" Ok");
  printf("[-] Initalization of idt:");
  idt_set_entry(0, USERMODE, (uint32_t)interrupt0);
  idt_set_entry(1, USERMODE, (uint32_t)interrupt1);
  idt_set_entry(2, USERMODE, (uint32_t)interrupt2);
  idt_set_entry(3, USERMODE, (uint32_t)interrupt3);
  idt_set_entry(4, USERMODE, (uint32_t)interrupt4);
  idt_set_entry(5, USERMODE, (uint32_t)interrupt5);
  idt_set_entry(6, USERMODE, (uint32_t)interrupt6);
  idt_set_entry(7, USERMODE, (uint32_t)interrupt7);
  idt_set_entry(8, KERNELMODE, (uint32_t)interrupt8);
  idt_set_entry(9, KERNELMODE, (uint32_t)interrupt9);
  idt_set_entry(10, USERMODE, (uint32_t)interrupt10);
  idt_set_entry(11, USERMODE, (uint32_t)interrupt11);
  idt_set_entry(12, USERMODE, (uint32_t)interrupt12);
  idt_set_entry(13, USERMODE, (uint32_t)interrupt13);
  idt_set_entry(14, USERMODE, (uint32_t)interrupt14);
  idt_set_entry(15, KERNELMODE, (uint32_t)interrupt15);
  idt_set_entry(16, USERMODE, (uint32_t)interrupt16);
  idt_set_entry(17, USERMODE, (uint32_t)interrupt17);
  idt_set_entry(18, USERMODE, (uint32_t)interrupt18);
  idt_set_entry(19, USERMODE, (uint32_t)interrupt19);
  idt_set_entry(20, USERMODE, (uint32_t)interrupt20);
  idt_set_entry(21, KERNELMODE, (uint32_t)interrupt21);
  idt_set_entry(22, KERNELMODE, (uint32_t)interrupt22);
  idt_set_entry(23, KERNELMODE, (uint32_t)interrupt23);
  idt_set_entry(24, KERNELMODE, (uint32_t)interrupt24);
  idt_set_entry(25, KERNELMODE, (uint32_t)interrupt25);
  idt_set_entry(26, KERNELMODE, (uint32_t)interrupt26);
  idt_set_entry(27, KERNELMODE, (uint32_t)interrupt27);
  idt_set_entry(28, KERNELMODE, (uint32_t)interrupt28);
  idt_set_entry(29, KERNELMODE, (uint32_t)interrupt29);
  idt_set_entry(30, USERMODE, (uint32_t)interrupt30);
  idt_set_entry(31, KERNELMODE, (uint32_t)interrupt31);

  // irq remapping
  idt_set_entry(32, KERNELMODE, (uint32_t)irq0);
  idt_set_entry(33, KERNELMODE, (uint32_t)irq1); // keyboard
  idt_set_entry(34, KERNELMODE, (uint32_t)irq2);
  idt_set_entry(35, KERNELMODE, (uint32_t)irq3);
  idt_set_entry(36, KERNELMODE, (uint32_t)irq4);
  idt_set_entry(37, KERNELMODE, (uint32_t)irq5);
  idt_set_entry(38, KERNELMODE, (uint32_t)irq6);
  idt_set_entry(39, KERNELMODE, (uint32_t)irq7);
  idt_set_entry(40, KERNELMODE, (uint32_t)irq8);
  idt_set_entry(41, KERNELMODE, (uint32_t)irq9);
  idt_set_entry(42, KERNELMODE, (uint32_t)irq10);
  idt_set_entry(43, KERNELMODE, (uint32_t)irq11);
  idt_set_entry(44, KERNELMODE, (uint32_t)irq12);
  idt_set_entry(45, KERNELMODE, (uint32_t)irq13);
  idt_set_entry(46, KERNELMODE, (uint32_t)irq14);
  idt_set_entry(47, KERNELMODE, (uint32_t)irq15);
  
  idt_set_entry(0x80, USERMODE, (uint32_t)interrupt128);

  idt_load((uint32_t)&idt_ptr);
  puts(" Ok");
}
