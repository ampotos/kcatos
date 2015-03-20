#include "string.h"
#include "morpion.h"
#include "puissance4.h"

typedef struct __programs_t{
  char *name;
  int (*function)(char **, char *);
} programs_t;

void start_kksh();

int main(){
  char line[4096];

  start_kksh(line);
  return (0);
}

void put_prompt(){
  write(1, &("> "), 2);
}

void execsh(const programs_t *prog, char *line){  
  char **g = NULL;
  int i = 0;

    for (i = 0;prog[i].function != NULL;++i){
      if (kstrncmp(prog[i].name, line, kstrlen(prog[i].name)) == 0)
	(*(prog[i].function))(g, line);
    }
}

void start_kksh(char *line){

  /*fisrt conponent is the command line programme
    name and second parameter is the programme address
  */

  const programs_t prog[] = {
    {"tictactoe", &tictactoe},
    {"connectFour", &connectFour},
    {"", NULL}
  };

  for(;;){
    put_prompt();
    line = get_input_line(line);
    execsh(prog, line);
  }
}
