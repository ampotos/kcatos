/*
** page.h for  in /home/eax/dev/kcatos/memory
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sat Dec 27 11:12:49 2014 eax
** Last update Tue Feb 10 18:01:23 2015 eax
*/

#ifndef PAGE_H_
#define PAGE_H_

#include <utils/types.h>

#define PAGE_SIZE (0x1000)
#define PAGE_TABLE_NB (1024)

typedef struct s_page
{
  u32	p:1;
  u32	rw:1;
  u32	us:1;
  u32	pwt:1;
  u32	pcd:1;
  u32	a:1;
  u32	d:1;
  u32	ps:1;
  u32	g:1;
  u32	ignored:3;
  u32	frame:20;
} t_page;

typedef struct s_page_table
{
  t_page pages[PAGE_TABLE_NB];
} t_page_table;

typedef struct s_page_directory
{
  t_page_table	*tables[PAGE_TABLE_NB];
  u32		tables_phys[PAGE_TABLE_NB];
  u32		phys;
} t_page_directory;

void	init_paging();
t_page	*get_page(u32 addr, int create, t_page_directory *dir);
void	enable_paging(u32 dir);

#endif

