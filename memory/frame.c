/*
** frame.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Mon Dec 29 00:47:35 2014 eax
** Last update Wed Feb 11 02:16:23 2015 eax
*/

#include <utils/types.h>
#include <utils/assert.h>
#include <memory/frame.h>
#include <memory/page.h>
#include <memory/kmalloc.h>

static t_frames g_frames;

void	init_frame()
{
  g_frames.nb_frames = PHYSICAL_MEMORY_SIZE / PAGE_SIZE;
  g_frames.used_frames = (void*)kmalloc(sizeof(*g_frames.used_frames) * g_frames.nb_frames);
  memset((u32)g_frames.used_frames, 0, sizeof(*g_frames.used_frames) * g_frames.nb_frames);
}

static void	set_frame(u32 addr)
{
  addr /= PAGE_SIZE;
  assert(addr < g_frames.nb_frames);
  g_frames.used_frames[addr] = 1;
}

static void	clear_frame(u32 addr)
{
  addr /= PAGE_SIZE;
  assert(addr < g_frames.nb_frames);
  g_frames.used_frames[addr] = 0;
}

static s32	get_available_frame()
{
  u32	i;

  for (i = 0 ; i < g_frames.nb_frames ; i++)
    if (!g_frames.used_frames[i])
      return (i);
  return (-1);
}

void	alloc_frame(t_page *page, int kernel_lvl, int writeable)
{
  s32	idx;

  assert(page->frame == 0);
  idx = get_available_frame();
  assertm(idx != -1, "no more memory available");
  set_frame(idx * PAGE_SIZE);
  page->p = 1;
  page->rw = writeable ? 1 : 0;
  page->us = kernel_lvl ? 0 : 1;
  page->frame = idx;
}

void	free_frame(t_page *page)
{
  assertm(page->frame != 0, "This page had no any associated frame");
  clear_frame(page->frame);
  page->frame = 0;
}
