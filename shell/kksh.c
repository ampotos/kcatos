#include "string.h"

typedef struct __programs_t{
  char *name;
  int (*function)(const char **);
} programs_t;

int main(){
  return start_kksh();
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

int morpion(const char **argv){
  printf("Welcom in Tic Tac Toe\n");
  printf("Good bye!\n");
}
  
int start_kksh(){
  const programs_t prog[] = {
    {"tictactoe", &morpion}, 
    {"", NULL}
  };
  
  for(;;){
    put_prompt();
    char *command = get_input_line();
    if (command != NULL)
      execsh(command, prog);
  }
}
