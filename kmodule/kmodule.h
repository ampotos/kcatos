/*
** kmodule.h for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 06:54:04 2015 eax
** Last update Wed Feb 25 07:43:57 2015 eax
*/

#ifndef KMODULE_H_
#define KMODULE_H_

#include <elf/elf.h>
#include <initrd/initrd.h>

enum e_kmod_exec {KMODULE_EXEC_KERNELLAND, KMODULE_EXEC_USERLAND};

void	kmodule_exec(t_elfparse *ep, enum e_kmod_exec);
int	kmodule_load_all(t_initrd_kmod *km, t_elfparse_symb **ksym);
int	kmodule_load_by_name(char *name, t_initrd_kmod *km, t_elfparse_symb **ksym);
int	kmodule_exec_by_name(char *name,
			       t_initrd_kmod *km,
			       enum e_kmod_exec);
#endif
