#include "pipex.h"


char *get_path(char **envp)
{
    int i = 0;
    char *variable;
    while (envp[i] != NULL)
    {
         variable = ft_substr(envp[i], 0, 5);
         if (ft_strncmp("PATH=", variable, 5) == 0)
             return (free(variable), &envp[i][5]);
         free(variable);
         i++;
    }
    return (free(variable), NULL);
}

char *path_exists(char **path, char *program)
{
    int i;
    char *program_path;
    char *swap;

    i = 0;
    while (path[i] != NULL)
    {
        swap = ft_strjoin(path[i], "/");
        program_path = ft_strjoin(swap, program);
        free(swap);
        if (!access(program_path, X_OK))
            return program_path;
        free(program_path);
        i++;
    }
    return NULL;
}


void free_double_ptr(void **ptr)
{
    int i = 0;
    while (ptr[i] != NULL)
    {
        free(ptr[i]);
        i++;
    }
    free(ptr);
}
