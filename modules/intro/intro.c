/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Tue Mar  3 16:49:26 2015 
*/
   
int	init_module(void *d)
{
  int	stop;
  char	buff[1024];
  
  if (!syscall_is_computer_on())
    if (syscall_is_computer_on_fire())
      {
        syscall_puts_screen("Oh sheat! Fire! Fire! Fire!");
  	syscall_puts_screen("Lets get out of there!");
  	*((unsigned*)init_module) /= ((unsigned)init_module)&0;
      }

  syscall_puts_screen("Hi. This is KCatOs. Deal with it.\twork");
  /* syscall_oh_crap(); */

  /* stop = 0; */
  /* while (!stop) */
  /*   { */

  while(45)
    {
      char c;
      read(&c, 1);
      printf("%c\n", (int)c);
    }
  /* while (syscall_keyboard_char_to_read()) */
      /* 	{ */
      /* 	  syscall_keyboard_getchar(); */
      /* 	  stop = 1; */
      /* 	} */
      
    /* } */
  syscall_puts_screen("cool");
  /* syscall_wait_until_the_end_of_your_life(); */
  return (0);
}
