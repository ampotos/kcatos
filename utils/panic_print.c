#include "../utils/Print.h"
#include "../descriptor_tables/idt.h"
#include <stdint.h>

const char	*tab_exception[20] =
  {
    "Division by zero",
    "Debugger",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bounds",
    "Invalid Opcode",
    "Coprocessor not available",
    "Double fault",
    "Coprocessor Segment Overrun",
    "Invalid Task State Segment",
    "Segment not present",
    "Stack Fault",
    "General protection fault",
    "Page fault",
    "reserved",
    "Math Fault",
    "Alignement Check",
    "Machine Check",
    "SIMD Floating-Point Exception"
  };

void		panic_print(regs_t reg)
{
  printf("KCat Panic !\n");
    /* Print du numéro de l'exception et le message qui en est lié */
  if (reg.int_no <= 19)
    printf("Exception happened: %32u, %s\n", reg.int_no, tab_exception[reg.int_no]);
  else
    printf("This error doesn't exit\n");

  /* Print du err_code */
  if (reg.err_code != 0)
    printf("err_code: %32h\n", reg.err_code);

  
  /* Print eip */
  printf("======= REGISTERS =======\n");
  printf("eip: %32h\n", reg.eip);

  /* Print de tous des registres edi, esi, ebp, esp, ebx, edx, ecx, eax; */
  printf("edi: %32h\t esi: %32h\t ebp: %32h\t esp: %32h\n", reg.edi, reg.esi, reg.ebp, reg.esp);
  printf("ebx: %32h\t edx: %32h\t ecx: %32h\t eax: %32h\n", reg.ebx, reg.edx, reg.ecx, reg.eax);

  /* Print de ds es ss */
  printf("ds:  %32h\t cs:  %32h\t ss:  %32h\n", reg.ds, reg.cs, reg.ss);
  
  printf("eflags: %32h\n", reg.eflags);
  
  /* Print stack */
  printf("======= STACK =======\n");
  for (int i = 0; i < 30; ++i)
  {
    printf("%32h\t", ((int*)(reg.esp))[i]);
    if ((i + 1) % 6 == 0)
      printf("\n");
  }
  printf("\n");
}
