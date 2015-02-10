/*
** syscall_handler.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Tue Feb 10 00:19:46 2015 eax
** Last update Tue Feb 10 01:59:23 2015 eax
*/

#ifndef SYSCALL_HANDLER_H_
#define SYSCALL_HANDLER_H_

#include <descriptor_tables/idt.h>

void	syscall_handler(regs_t *regs);

#endif
