/*
** error.c for  in /home/eax/dev/kcatos/elf
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Feb 23 06:58:23 2015 eax
** Last update Mon Feb 23 06:59:41 2015 eax
*/

#include <utils/error.h>
#include <utils/print.h>

int	reter(int val, char *msg)
{
  printf("%s\n", msg);
  return (val);
}
