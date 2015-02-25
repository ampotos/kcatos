/*
** kmodule.h for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 06:54:04 2015 eax
** Last update Wed Feb 25 04:50:13 2015 eax
*/

#ifndef KMODULE_H_
#define KMODULE_H_

#include <elf/elf.h>
#include <initrd/initrd.h>

int	kmodule_load(t_initrd_kmod *km, t_elfparse_symb **ksym);
#endif
