//
// read.h for KCatOS in /home/ampotos/kcatos
// 
// Made by 
// Login   <ampotos@epitech.net>
// 
// Started on  Tue Mar  3 15:40:21 2015 
// Last update Tue Mar  3 16:01:16 2015 
//

#ifndef READ_H_
#define READ_H_

u32     read(char *buff, u32 size);
u32     read_non_block(char *buff, u32 size);

u32     read_raw(char *buff, u32 size);
u32     read_raw_non_block(char *buff, u32 size);

#endif
