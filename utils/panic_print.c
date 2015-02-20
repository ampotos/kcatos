#include <utils/print.h>
#include <descriptor_tables/idt.h>
#include <stdint.h>
#include <utils/usefull_routine.h>

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

void	handle_err_code(u32 num, u32 err)
{
  printf("err_code: %32h", err);
  if (num == IDT_PAGE_FAULT)
    {
      u32 fault_addr;

      asm volatile("mov %%cr2, %0" : "=r" (fault_addr));
      printf(" (");
      
      if (err & 0x1)
	puts_nolf("page protected violation | ");
      else
	puts_nolf("page not present | ");

      if (err & 0x8)
	puts_nolf("reserved field not empty | ");

      
      if (err & 0x2)
	puts_nolf("by write ");
      else
	puts_nolf("by read ");

      if (err & 0x4)
	puts_nolf("from user-mode ");
      else
	puts_nolf("from kernel-mode ");
      
      printf("at %x)", fault_addr);
    }
  puts("");
}

void		panic_print(regs_t reg)
{
  printf("KCat Panic Attack!\n");
    /* Print du numéro de l'exception et le message qui en est lié */
  if (reg.int_no <= 19)
    printf("Exception happened: %32u, %s\n", reg.int_no, tab_exception[reg.int_no]);
  else
    printf("This error doesn't exit\n");

  /* Print du err_code */
  if (reg.have_errcode != 0)
    handle_err_code(reg.int_no, reg.err_code);

  
  /* Print eip */
  puts("");
  printf("======= REGISTERS =======\n");
  printf("eip: %32h\n", reg.eip);

  /* Print de tous des registres edi, esi, ebp, esp, ebx, edx, ecx, eax; */
  printf("edi: %32h\t esi: %32h\t ebp: %32h\t esp: %32h\n", reg.edi, reg.esi, reg.ebp, reg.esp);
  printf("ebx: %32h\t edx: %32h\t ecx: %32h\t eax: %32h\n", reg.ebx, reg.edx, reg.ecx, reg.eax);

  /* Print de ds es ss */
  printf("ds:  %32h\t cs:  %32h\t ss:  %32h\n", reg.ds, reg.cs, reg.ss);
  
  printf("eflags: %32h\n", reg.eflags);

  /* Print stack */
  puts("");
  printf("======= STACK =======\n");
  for (int i = 0; i < 30; ++i)
  {
    printf("%32h\t", ((int*)(reg.esp))[i]);
    if ((i + 1) % 6 == 0)
      printf("\n");
  }
  printf("\n");
}

void	panic_print_assert(char *filename, int linenum, char *expr, char *msg)
{
  printf("KCat Panic Attack !\n");
  printf("An assertion failed.\n");
  printf("%s:%d -> (%s) %s \n", filename, linenum, expr, msg ? msg : "");
  wait_until_the_end_of_your_life();  
}
