/*
** syscall.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 01:09:20 2015 eax
** Last update Fri Feb 13 23:06:16 2015 eax
*/

#include <syscall/syscall.h>
#include <utils/types.h>

DEFN_SYSCALL0(wait_until_the_end_of_your_life, 0);
DEFN_SYSCALL2(write_screen, 1, const char*, u32);
DEFN_SYSCALL1(puts_screen, 2, const char*);
DEFN_SYSCALL0(is_computer_on, 3);
DEFN_SYSCALL0(is_computer_on_fire, 4);
DEFN_SYSCALL0(oh_crap, 5);
DEFN_SYSCALL1(sbrk, 6, u32);
