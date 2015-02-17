#include "string.h"

//get the command line from user
char *get_input_line(){
  char *line = KMALLOC(BLOC_SIZE);
  int i = 0;
  int maxAlloc = BLOC_SIZE;
  char c;
  int ret;
  
  if (line == NULL)
    {
      printf("ERROR: Memory allocation error!\n");
      return NULL;
    }
  while ((ret = read(0, &c, 1)) > 0 && c != '\n'){
    if (i >= maxAlloc){
      if ((line = KREALLOC(line, i + BLOC_SIZE)) == NULL)
	{
	  printf("ERROR: Memory allocation error!\n");
	  return NULL;
	}
    }
    line[i++] = c;
  }
  line[i] = 0;
  if (ret < 1)
    printf("ERROR: read!\n");
  return line;
}

//return the number of strings delimited by the bytes contained in tok
int countok(char *s, char *tok){
  int ctr = 0;
  
  while (*s){
    if (!kstrspn(s, tok)){
      if (s[1] == 0 || kstrspn(&s[1], tok))
	++ctr;
    }
    *s++;
  }
  return ctr;
}

char **str_to_word_tab(register char *s){
  char **ret = NULL;
  int i = 1;
  int len = countok(s, " \t");
  
  if (len == 0)
    return NULL;
  if ((ret = KMALLOC((len + 1) * sizeof(char *))) == NULL)
    return NULL;

  ret[0] = kstrtok(s, " \t");
  ret[len] = NULL;

  while (i < len)
    ret[i++] = kstrtok(NULL, " \t");
  return ret;
}