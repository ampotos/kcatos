/*
** assert.h for  in /home/eax/dev/kcatos/res/the_heap
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Thu Dec 25 19:14:01 2014 eax
** Last update Tue Feb 10 13:45:19 2015 eax
*/

#ifndef ASSERT_H_
#define ASSERT_H_

#include <utils/print.h>

#define assert(expr) ((expr) ? (void)0 : panic_print_assert(__FILE__, __LINE__, #expr))

#endif
