/*
** idt.h for kcatos in /home/ampotos/kcatos/interrupt_table
** 
** Made by 
** Login   <ampotos@epitech.net>
** 
** Started on  Mon Dec  8 12:02:10 2014 
// Last update Fri Feb 20 19:00:52 2015 
*/

#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

#define KERNELMODE (0)
#define USERMODE (3)

#define IDT_DIVIDE_BY_0		0	// division by 0
#define IDT_SINGLE_STEP		1	// single stepexecution for debugger
#define IDT_NMI			2	// non maskable interrupt
#define IDT_BREAKPOINT		3	// breakpoint for debugger
#define IDT_OVERFLOW		4	// overflow in cpu operation
#define IDT_BOUNDS_CHECK	5	// bounds check
#define IDT_UNDEF_OPCODE	6	// undefined opcode
#define IDT_NO_COPROCESSOR	7	// no coporecessor (like module but for cpu)
#define IDT_DOUBLE_FAUlT	8	// double fault = problem when processor try to execute an interrupt or exception   push an error code
#define IDT_COPRO_SEG_OVER	9	// coprocessor segment overrun : in protected mode it's occure if there is a page or segmentation problem during transfer middle portion of coprocessor to the NPX
#define IDT_INVALID_TSS		10	// invalide task State Segment (contexte d'un processus) push an error code
#define IDT_NO_SEGMENT		11	// segment not present push an error code
#define IDT_STACK_EXCEPTION	12	// Stack fault push an error code
#define IDT_GEN_PROTE_FAULT	13	// cpu error not handle by an other interrupt push an error code
#define IDT_PAGE_FAULT		14	// page fault push an error code
#define IDT_RESERVED		15	// intel RESERVED
#define IDT_FLOATING_ERROR	16	// floating point exception
#define IDT_ALIGN_CHECK		17	// Alignement error
#define IDT_MACHINE_CHECH	18	// hardware probleme (lke bus error for example)

/* ***************************************/
/* Number 19 to 31 are intel reserved    */
/*****************************************/

/* *******************************/
/* Number 32 to 39 master pic    */
/*********************************/

/* ******************************/
/* Number 40 to 47 slave pic    */
/********************************/

#define IDT_SYSCALL		0x80    // syscall

/* Number 47 to 255 can be defined by us */

typedef struct regs
{
  uint32_t ds;				                // Data segment selector
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;	// Pushed by pusha.
  uint32_t int_no, have_errcode;				// Interrupt number and flag if errcode
  uint32_t err_code;					// error code (if applicable)
  uint32_t eip, cs, eflags, useresp, ss;		// Pushed by the processor automatically.
} regs_t;

typedef struct s_idt_entry
{
  uint16_t base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
  uint16_t sel;                 // Kernel segment selector.
  uint8_t  always0;             // This must always be zero.
  uint8_t  magic:5;             // magic value
  uint8_t  dpl:2;	        // pribvilège level
  uint8_t  p:1;			// entry is present
  uint16_t base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed)) t_idt_entry;

typedef struct s_idt_ptr
{
  uint16_t limit;
  uint32_t base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed)) t_idt_ptr;

void	idt_load(uint32_t idt_ptr);
void	setup_idt();

extern void interrupt0 ();
extern void interrupt1 ();
extern void interrupt2 ();
extern void interrupt3 ();
extern void interrupt4 ();
extern void interrupt5 ();
extern void interrupt6 ();
extern void interrupt7 ();
extern void interrupt8 ();
extern void interrupt9 ();
extern void interrupt10();
extern void interrupt11();
extern void interrupt12();
extern void interrupt13();
extern void interrupt14();
extern void interrupt15();
extern void interrupt16();
extern void interrupt17();
extern void interrupt18();
extern void interrupt19();
extern void interrupt20();
extern void interrupt21();
extern void interrupt22();
extern void interrupt23();
extern void interrupt24();
extern void interrupt25();
extern void interrupt26();
extern void interrupt27();
extern void interrupt28();
extern void interrupt29();
extern void interrupt30();
extern void interrupt31();
extern void interrupt128();

#endif
