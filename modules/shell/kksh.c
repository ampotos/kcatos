#include "string.h"

typedef struct __programs_t{
  char *name;
  int (*function)(char *);
} programs_t;


/*int main(){
  start_kksh();
  return (0);
}*/

void put_prompt(){
  syscall_write_screen("> ", 2);
}

void execsh(char *command, const programs_t *prog) {
  char buff[BLOC_SIZE];
  int i;
  
  if ((get_arg(buff, BLOC_SIZE, command, 0)) == -1)
    return ;

  for (i = 0; prog[i].function != NULL; ++i) {
    if (kstrcmp(prog[i].name, buff) == 0)
        (*(prog[i].function))(command);
  }

/*
  char **g = str_to_wo rd_tab(command);
  int i = 0;

  if (g){
    for (i = 0;prog[i].function != NULL;++i){
      if (g[0] != NULL && kstrcmp(prog[i].name, g[0]) == 0)
	(*(prog[i].function))(g);
    }
  }
  KFR EE(g);
  KFR EE(command);
*/
}

//program test
int morpion(char *argv){
  syscall_puts_screen("Welcom in Tic Tac Toe\n");
  syscall_puts_screen("Good bye!\n");
}

void start_kksh() {
  char  command[BLOC_SIZE];

  const programs_t prog[] = {
    {"tictactoe", &morpion}, 
    {"", NULL}
  };

  int (*functio)(char *);

  functio = &morpion;
  functio(NULL);
  
  for(;;){
    put_prompt();
    if (get_input_line(command, BLOC_SIZE) == -1)
    {
      syscall_puts_screen("READ ERROR");
      continue;
    }
    //syscall_puts_screen("Prout !2");
    execsh(command, prog);
  }
}
