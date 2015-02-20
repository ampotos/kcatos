/*
** test_kmalloc.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Wed Feb 11 00:33:57 2015 eax
** Last update Wed Feb 11 00:36:03 2015 eax
*/

#include <utils/print.h>
#include <memory/kmalloc.h>

void	*test_fill_km(int sz)
{
  int	i;
  char *p;

  p = kmalloc(sz);
  printf("km(%d) => %x\n", sz, p);
  
  for (i = 0 ; i < sz ; i++)
    p[i] = 0x41;
  return (p);
}

void	fuzzing_kmalloc_kfree()
{
  void	*tblptr[1000];
  u32	super_rand;
  u32	i;
  u32	sum;

  sum = 0;
  for (i = 0 ; i < 100 ; i++)
    {
      super_rand = ((42 << i)^(i<<(i*3))) / 3 % 300;
      tblptr[i] = kmalloc(super_rand);
      sum += super_rand;
      printf("%d: Currently allocated: %d Bytes\n", i, sum);
    }
  puts("Time to free");
  for (i = 0 ; i < 100 ; i++)
    kfree(tblptr[i]);
}

  
