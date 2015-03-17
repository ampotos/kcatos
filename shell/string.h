/* #include <syscall/syscall.h> */

#include <stdlib.h>
#include <stdio.h>

#define syscall_puts_screen puts
#define write_screen(x, y) write(0, x, y)

#ifndef NULL
#define NULL 0x0
#endif

#define KMALLOC malloc
#define KFREE free
#define KREALLOC mrealloc
#define BLOC_SIZE 1024

/* void	*malloc(unsigned); */
/* void	*realloc(void *, unsigned); */
/* void	free(void *); */

char line[4096];

char * kstrchr(const char *s, int c);
char *kstrpbrk(register const char *s, register const char *accept);
int kstrspn(const char *s, const char *accept);
char * kstrtok(register char *s, register const char *delim);
int kstrcmp(const char *p1, const char *p2);
char *get_input_line(char *line);
int countok(char *s, char *tok);
char **str_to_word_tab(register char *s);
