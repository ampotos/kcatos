//
// pic.h for KcatOS in /home/ampotos/kcatos/descriptor_tables/pic
// 
// Made by 
// Login   <ampotos@epitech.net>
// 
// Started on  Wed Feb 11 17:52:02 2015 
// Last update Sun Mar  8 18:53:25 2015 
//

#include <descriptor_tables/idt.h>
#include <utils/types.h>

#ifndef PIC_H
#define PIC_H

void	init_irq();

void	irq_handler(regs_t *regs);

void	keyboard_handler();

void	pit_handler();
void	incr_pit();
void	sleep(u32 time);

void	setup_pit(u32 freq);

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

typedef struct s_ticks
{
  u32	high;
  u32	low;
} t_ticks;

extern char *buff;
extern t_ticks ticks;
extern u32 ct_read;

#endif
