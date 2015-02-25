/*
** multiboot.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 22:56:36 2015 eax
** Last update Mon Feb 23 17:48:44 2015 eax
*/

#ifndef MULTIBOOT_H_
#define MULTIBOOT_H_

#include <utils/types.h>

/* http://www.gnu.org/software/grub/manual/multiboot/multiboot.html */

typedef struct
{
  u32 flags;
  u32 mem_lower;
  u32 mem_upper;
  u32 boot_device;
  u32 cmdline;
  u32 mods_count;
  u32 mods_addr;
  u32 num;
  u32 size;
  u32 addr;
  u32 shndx;
  u32 mmap_length;
  u32 mmap_addr;
  u32 drives_length;
  u32 drives_addr;
  u32 config_table;
  u32 boot_loader_name;
  u32 apm_table;
  u32 vbe_control_info;
  u32 vbe_mode_info;
  u32 vbe_mode;
  u32 vbe_interface_seg;
  u32 vbe_interface_off;
  u32 vbe_interface_len;
}  __attribute__((packed)) t_multiboot;

#endif
