#include "string.h"


typedef struct __programs_t{
  char *name;
  int (*function)(char *);
} programs_t;

int connectFour(char *args);
int tictactoe(char *args);
//int swascii(char *arg);

int cleanWrap(char *arg)
{
  (void)arg;
  clean();
  terminal_setpos(0, 0);
  terminal_setcolor(make_color(COLOR_LIGHT_GREY, COLOR_BLACK));
  return (0);
}

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
    {
        (*(prog[i].function))(command);
        break;
    }
  }

  if (prog[i].function == NULL)
  {
    syscall_puts_screen("Unvalible command. List of avalible command :");
    for (i = 0; prog[i].function != NULL; ++i) {
      printf("  -  %s\n", prog[i].name);
    }
    printf("  -  exit\n");
  }
}

void start_kksh() {
  char  command[BLOC_SIZE];

  const programs_t prog[] = {
    {"tictactoe", &tictactoe}, 
    {"connectFour", &connectFour}, 
//    {"sw", &swascii}, 
    {"clear", &cleanWrap},
    {"", NULL}
  };

  cleanWrap(NULL);
  
  for(;;){
    put_prompt();
    if (get_input_line(command, BLOC_SIZE) == -1)
    {
      syscall_puts_screen("READ ERROR");
      continue;
    }
    if (!kstrcmp(command, "exit"))
      return ;
    //syscall_puts_screen("Prout !2");
    execsh(command, prog);
  }
}
