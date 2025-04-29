#include "pipex.h"

void check_fork_failure(int id)
{
   if (id == -1)
       ft_error("Fork failure\n", true);
   return ;
}

void free_all(char **binpaths, char **cmd1, char **cmd2, bool free_first_only)
{
    if (free_first_only == false)
    {
        free(binpaths[1]);
        free_double_ptr((void **)cmd2);
    }
    free(binpaths[0]);
    free_double_ptr((void **)cmd1);
}


void cleanup(int *id, int *fd, char **binpaths, char **cmd1, char **cmd2)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(id[0], NULL, 0);
    waitpid(id[1], NULL, 0);
    free_all(binpaths, cmd1, cmd2, false);
}

void ft_error(char *str, bool exit_program)
{
	int i;
	i = 0;
	write(2, "Error: ", 8);
	while(str[i] != '\0')
		write(2, &str[i++], 1);
	if (exit_program == true)
		exit(1);
}
