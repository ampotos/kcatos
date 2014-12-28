/*
** kmalloc.h for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Dec 28 13:38:10 2014 eax
** Last update Sun Dec 28 13:38:25 2014 eax
*/

#ifndef KMALLOC_H_
#define KMALLOC_H_

#include <utils/types.h>

u32	bootstrap_kmalloc(u32 size, u32 *phys, u32 aligned);

#endif
