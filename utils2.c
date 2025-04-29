#include "pipex.h"

void ft_error_exit(char *str, int errorcode)
{
	int i;
	i = 0;
	write(2, "Error: ", 8);
	while(str[i] != '\0')
		write(2, &str[i++], 1);
	exit(errorcode);
}
