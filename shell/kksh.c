#include "string.h"

typedef struct __programs_t{
  char *name;
  int (*function)(char **);
} programs_t;

void start_kksh();

int main(){
  start_kksh();
  return (0);
}

void put_prompt(){
  write(1, &("> "), 2);
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

void start_kksh(){

  /*fisrt conponent is the command line programme
    name and second parameter is the programme address
  */
  const programs_t prog[] = {
    {"tictactoe", &morpion},
    {"connectFour", &puissance4},
    {"", NULL}
  };

  for(;;){
    put_prompt();
    char *command = get_input_line();
    if (command != NULL)
      execsh(command, prog);
  }
}
