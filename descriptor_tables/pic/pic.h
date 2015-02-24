//
// pic.h for KcatOS in /home/ampotos/kcatos/descriptor_tables/pic
// 
// Made by 
// Login   <ampotos@epitech.net>
// 
// Started on  Wed Feb 11 17:52:02 2015 
// Last update Tue Feb 24 19:16:38 2015 
//

#include <descriptor_tables/idt.h>
#include <utils/types.h>

void	init_irq();

void	irq_handler(regs_t *regs);

void keyboard_handler();

void setup_pit(u32 freq);

extern char *buff;

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
