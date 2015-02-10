/*
** syscall.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 01:09:20 2015 eax
** Last update Tue Feb 10 02:51:09 2015 eax
*/

#include <syscall/syscall.h>
#include <utils/types.h>
#include <utils/usefull_routine.h>

DEFN_SYSCALL0(wait_until_the_end_of_your_life, 0);
DEFN_SYSCALL2(write_screen, 1, const char*, u32);
DEFN_SYSCALL1(puts_screen, 2, const char*);