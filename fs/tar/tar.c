/*
** tar.c for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 20:40:56 2015 eax
** Last update Wed Feb 25 06:02:26 2015 eax
*/

#include <utils/types.h>
#include <utils/string.h>
#include <fs/tar/tar.h>

static u32	stroct2int(char *s)
{
  u32	res;

  res = 0;
  while (*s)
    {
      res *= 8;
      res += *s - '0';
      s++;
    }
  return (res);
}

static void	ustar_to_human(t_tar_ustar_header *us,
			       t_tar_human_header *hu,
			       char *data)
{
  memcpy(hu->name, us->name, 100);
  hu->nameptr = (data - 512) +
    offsetof(t_tar_ustar_header, name);
  hu->mode = stroct2int(us->mode);
  hu->uid = stroct2int(us->uid);
  hu->gid = stroct2int(us->gid);
  hu->size = stroct2int(us->size);
  hu->mtime = stroct2int(us->mtime);
  hu->chksum = stroct2int(us->chksum);
  memcpy(hu->linkname, us->linkname, 100);
  memcpy(hu->magic, us->magic, 6);
  memcpy(hu->version, us->version,6);
  memcpy(hu->uname, us->uname, 32);
  memcpy(hu->gname, us->gname, 32);
  hu->devmajor = stroct2int(us->devmajor);
  hu->devminor = stroct2int(us->devminor);
  memcpy(hu->prefix, us->prefix, 131);
}

u32	get_next_tar_node(char *tardata, t_tar_node *out_node)
{
  static char	*saved_tardata = NULL;

  if (tardata)
    saved_tardata = tardata;
  if (saved_tardata[0] == 0)
    return (0);
  if (!out_node)
    return (0);

  out_node->raw_header = *(t_tar_ustar_header*)saved_tardata;
  out_node->data = saved_tardata + 512;
  ustar_to_human(&out_node->raw_header, &out_node->header, out_node->data);
  
  saved_tardata += (512 + out_node->header.size + 512) & ~(512-1);
  
  return (out_node->header.size);
}
