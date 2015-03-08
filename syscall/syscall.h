/*
** syscall.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 00:34:36 2015 eax
// Last update Sun Mar  8 18:48:42 2015 
*/

#ifndef SYSCALL_H_
#define SYSCALL_H_

#include <utils/types.h>

#define DECL_SYSCALL0(fn) int syscall_##fn()
#define DECL_SYSCALL1(fn,p1) int syscall_##fn(p1)
#define DECL_SYSCALL2(fn,p1,p2) int syscall_##fn(p1,p2)
#define DECL_SYSCALL3(fn,p1,p2,p3) int syscall_##fn(p1,p2,p3)
#define DECL_SYSCALL4(fn,p1,p2,p3,p4) int syscall_##fn(p1,p2,p3,p4)
#define DECL_SYSCALL5(fn,p1,p2,p3,p4,p5) int syscall_##fn(p1,p2,p3,p4,p5)

#define DEFN_SYSCALL0_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num))
#define DEFN_SYSCALL1_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1))
#define DEFN_SYSCALL2_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2))
#define DEFN_SYSCALL3_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3))
#define DEFN_SYSCALL4_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3), "S" ((int)p4))
#define DEFN_SYSCALL5_ASM(num) asm volatile("int $0x80" : "=a" (a) : "0" (num), "b" ((int)p1), "c" ((int)p2), "d" ((int)p3), "S" ((int)p4), "D" ((int)p5))

#define DEFN_SYSCALL0_ARGS
#define DEFN_SYSCALL1_ARGS(P1) P1 p1
#define DEFN_SYSCALL2_ARGS(P1, P2) P1 p1, P2 p2
#define DEFN_SYSCALL3_ARGS(P1, P2, P3) P1 p1, P2 p2, P3 p3
#define DEFN_SYSCALL4_ARGS(P1, P2, P3, P4) P1 p1, P2 p2, P3 p3, P4 p4
#define DEFN_SYSCALL5_ARGS(P1, P2, P3, P4, P5) P1 p1, P2 p2, P3 p3, P4 p4, P5 p5

#define DEFN_SYSCALLx(ASM, fn, ARGS)		\
  int syscall_##fn(ARGS)			\
  {						\
    int a;					\
    ASM;					\
    return a;					\
  }

#define DEFN_SYSCALL0(fn, num)					\
  DEFN_SYSCALLx(DEFN_SYSCALL0_ASM(num), fn, DEFN_SYSCALL0_ARGS)
#define DEFN_SYSCALL1(fn, num, P1)				\
  DEFN_SYSCALLx(DEFN_SYSCALL1_ASM(num), fn, DEFN_SYSCALL1_ARGS(P1))
#define DEFN_SYSCALL2(fn, num, P1, P2)				\
  DEFN_SYSCALLx(DEFN_SYSCALL2_ASM(num), fn, DEFN_SYSCALL2_ARGS(P1, P2))
#define DEFN_SYSCALL3(fn, num, P1, P2, P3)			\
  DEFN_SYSCALLx(DEFN_SYSCALL3_ASM(num), fn, DEFN_SYSCALL3_ARGS(P1, P2, P3))
#define DEFN_SYSCALL4(fn, num, P1, P2, P3, P4)			\
  DEFN_SYSCALLx(DEFN_SYSCALL4_ASM(num), fn, DEFN_SYSCALL4_ARGS(P1, P2, P3, P4))
#define DEFN_SYSCALL5(fn, num, P1, P2, P3, P4, P5)		\
  DEFN_SYSCALLx(DEFN_SYSCALL5_ASM(num), fn, DEFN_SYSCALL5_ARGS(P1, P2, P3, P4, P5))




DECL_SYSCALL0(wait_until_the_end_of_your_life);
DECL_SYSCALL2(write_screen, const char*, u32);
DECL_SYSCALL1(puts_screen, const char*);
DECL_SYSCALL0(is_computer_on);
DECL_SYSCALL0(is_computer_on_fire);
DECL_SYSCALL0(oh_crap);
DECL_SYSCALL1(sbrk, u32);
DECL_SYSCALL0(kpause);
DECL_SYSCALL2(read, char *, u32);
DECL_SYSCALL2(read_non_block, char *, u32);
DECL_SYSCALL0(exit);
DECL_SYSCALL1(sleep, u32);

#endif
