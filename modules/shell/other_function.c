#include "string.h"

//get the command line from user
int		get_input_line(char *line, u32 size) {
	u32		ret, offset = 0;

	if (size < 5)
		return -1;
	do {
    	//syscall_puts_screen("ROLL");
		if (((int)size - (int)offset) < 0 || (ret = syscall_read(line + offset, size - offset)) == size)
			return -1;
		syscall_write_screen(line + offset, ret);
		offset += ret;
		line[offset] = '\0';
		//syscall_write_screen("Gain : ", 7);
		//syscall_puts_screen(line);
	} while (line[offset-1] != '\n');

	line[offset-1] = '\0';

	return offset - 1;
}

//return the number of strings delimited by the bytes contained in tok
int		countok(char *s, char *tok) {
 	int		ctr = 0;

	while (*s) {
		if (!kstrspn(s, tok)) {
			if (s[1] == 0 || kstrspn(&s[1], tok))
				++ctr;
		}

    	*s++;
	}

	return ctr;
}

int		count_arg(char *s) {
	return countok(s, " \t\n");
}

int		get_arg(char *buff, int buff_size, register char *s, int num) {
	int		i = 0;
	int		len = countok(s, " \t\n");
	char	*ret;
	char	*end;
  
  	*buff = '\0';
	if (len == 0 || len < num)
		return -1;

	ret = s;
	while (*ret && (*ret == ' ' || *ret == '\t' || *ret == '\n'))
		ret++;

	while (++i <= num && ret != NULL)
	{
		ret = kstrpbrk(ret, " \t\n");
		while (ret != NULL && *ret && (*ret == ' ' || *ret == '\t' || *ret == '\n'))
			ret++;
	}

	if (ret == NULL)
		return -1;

	end = kstrpbrk(ret, " \t\n");
	i = 0;
	buff_size--;

	while (i < buff_size && ((end == NULL && *ret != '\0') || (end != ret)))
		buff[i++] = *(ret++);

	if (end != ret && end != NULL)
		return -1;

	if (buff[i - 1] == ' ' || buff[i - 1] == '\t' || buff[i - 1] == '\n')
		buff[i - 1] = '\0';
	buff[i] = '\0';
	return 0;
}
