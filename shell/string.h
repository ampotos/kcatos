#ifndef NULL
#define NULL 0x0
#endif

#define KMALLOC malloc
#define KFREE free
#define KREALLOC realloc
#define BLOC_SIZE 1024

#include <stdlib.h>
#include <stdio.h>


char * kstrchr(const char *s, int c);
char *kstrpbrk(register const char *s, register const char *accept);
int kstrspn(const char *s, const char *accept);
char * kstrtok(register char *s, register const char *delim);
int kstrcmp(const char *p1, const char *p2);
char *get_input_line();
int countok(char *s, char *tok);
char **str_to_word_tab(register char *s);
