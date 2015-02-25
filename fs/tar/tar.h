/*
** tar.h for  in /home/eax/dev/kcatos
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Fri Feb 20 20:13:23 2015 eax
** Last update Wed Feb 25 05:52:34 2015 eax
*/

#ifndef TAR_H_
#define TAR_H_

#include <utils/types.h>

typedef struct s_tar_ustar_header
{                               /* byte offset */
  char name[100];               /*   0 */
  char mode[8];                 /* 100 */
  char uid[8];                  /* 108 */
  char gid[8];                  /* 116 */
  char size[12];                /* 124 */
  char mtime[12];               /* 136 */
  char chksum[8];               /* 148 */
  char typeflag;                /* 156 */
  char linkname[100];           /* 157 */
  char magic[6];                /* 257 */
  char version[2];              /* 263 */
  char uname[32];               /* 265 */
  char gname[32];               /* 297 */
  char devmajor[8];             /* 329 */
  char devminor[8];             /* 337 */
  char prefix[131];             /* 345 */
} t_tar_ustar_header;

typedef struct s_tar_human_header
{
  char name[100];
  char *nameptr;
  u32 mode;
  u32 uid;
  u32 gid;
  u32 size;
  u32 mtime;
  u32 chksum;
  char typeflag;
  char linkname[100];
  char magic[6];
  char version[2];
  char uname[32];
  char gname[32];
  u32 devmajor;
  u32 devminor;
  char prefix[131];
} t_tar_human_header;

typedef struct
{
  t_tar_ustar_header raw_header;
  t_tar_human_header header;
  char	*data;
} t_tar_node;

u32	get_next_tar_node(char *tardata, t_tar_node *out_node);

#endif
