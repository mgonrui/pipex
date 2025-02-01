#ifndef PIPEX_H
#define PIPEX_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "../libft/libft.h"
/* #include "../ft_printf/ft_printf.h" */

void free_double_ptr(void **ptr);
char *path_exists(char **path, char *program);
char *get_path(char **envp);

#endif // PIPEX_H
