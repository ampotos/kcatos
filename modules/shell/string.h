#include <syscall/syscall.h>
#include <utils/print.h>

//#include <stdlib.h>
//#include <stdio.h>

//#define syscall_puts_screen puts
//#define write_screen(x, y) write(0, x, y)

#ifndef NULL
#define NULL 0x0
#endif

#define BLOC_SIZE 1024

char * kstrchr(const char *s, int c);
char *kstrpbrk(register const char *s, register const char *accept);
int kstrspn(const char *s, const char *accept);
char * kstrtok(register char *s, register const char *delim);
int kstrcmp(const char *p1, const char *p2);

int countok(char *s, char *tok);

int		get_arg(char *buff, int buff_size, register char *s, int num);
int		get_input_line(char *line, u32 size);
int		count_arg(char *s);
