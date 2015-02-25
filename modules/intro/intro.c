/*
** s2.c for  in /home/eax/dev/kcatos/elf/samples
** 
** Made by eax
** Login   <soules_k@epitech.net>
** 
** Started on  Sun Feb 22 15:49:15 2015 eax
** Last update Wed Feb 25 07:25:40 2015 eax
*/

int	init_module(void *d)
{
  int	stop;
  
  if (!syscall_is_computer_on())
    if (syscall_is_computer_on_fire())
      {
        syscall_puts_screen("Oh sheat! Fire! Fire! Fire!");
	syscall_puts_screen("Lets get out of there!");
	*((unsigned*)init_module) /= ((unsigned)init_module)&0;
      }

  syscall_puts_screen("Hi. This is KCatOs. Deal with it.");
  syscall_oh_crap();

  stop = 0;
  while (!stop)
    {
      while (syscall_keyboard_char_to_read())
	{
	  syscall_keyboard_getchar();
	  stop = 1;
	}
    }
  syscall_puts_screen("cool");
  syscall_wait_until_the_end_of_your_life();
  return (0);
}
