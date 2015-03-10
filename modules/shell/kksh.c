#include "string.h"

typedef struct __programs_t{
  char *name;
  int (*function)(char **);
} programs_t;

void start_kksh();

void  *mrealloc(void *src, unsigned i) {
  void      *tmp = malloc(i);
  unsigned  cnt = 0;

  while (cnt <= i) {
    ((char *)tmp)[cnt] = ((char *)src)[cnt];
    cnt++;
  }

  free(src);

  return (tmp);
}

/*int main(){
  start_kksh();
  return (0);
}*/

void put_prompt(){
  syscall_puts_screen("> ");
}

void execsh(char *command, const programs_t *prog){  
  char **g = str_to_word_tab(command);
  int i = 0;

  if (g){
    for (i = 0;prog[i].function != NULL;++i){
      if (g[0] != NULL && kstrcmp(prog[i].name, g[0]) == 0)
	(*(prog[i].function))(g);
    }
  }
  KFREE(g);
  KFREE(command);
}

//program test
int morpion(char **argv){
  syscall_puts_screen("Welcom in Tic Tac Toe\n");
  syscall_puts_screen("Good bye!\n");
}

void start_kksh() {

  /*fisrt conponent is the command line programme
    name and second parameter is the programme address
  */
  const programs_t prog[] = {
    {"tictactoe", &morpion}, 
    {"", NULL}
  };
  
  for(;;){
    put_prompt();
    char *command = get_input_line();
    syscall_puts_screen("Prout !2");
    if (command != NULL)
      execsh(command, prog);
  }
}
