/*
** types.h for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Dec 27 11:13:44 2014 eax
** Last update Wed Feb 25 05:59:44 2015 eax
*/

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

#define NULL ((void*)0)
#define offsetof(type, member) ((u32) &((type *)0)->member)
				
typedef uint64_t	u64;
typedef int64_t		s64;
typedef uint32_t	u32;
typedef int32_t		s32;
typedef uint16_t	u16;
typedef int16_t		s16;
typedef uint8_t		u8;
typedef int8_t		s8;

typedef u32		size_t;

#endif

