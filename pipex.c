#include "pipex.h"
#include <asm-generic/errno-base.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>


/* char *get_command(char *argv) */
/* { */
/*    char *command; */
/*    int i; */

/*    i = 0; */
/*    while (argv[i] != ' ') */
/*    { */
/*        i++; */
/*    } */
/*    command = malloc(i + 1 * sizeof(char)); */
/*    if (command == NULL) */
/*        return NULL; */
/*    i = 0; */
/*    while (argv[i] != ' ') */
/*    { */
/*        command[i] = argv[i]; */
/*        i++; */
/*    } */
/*    argv[i] = '\0'; */
/*    return command; */
/* } */




int main(int argc, char **argv)
{
    char **command1;
    char **command2;

    command1 = ft_split(argv[1], ' ');
    command2 = ft_split(argv[2], ' ');

    command1[0] = ft_strjoin("/usr/bin/", command1[0]);
    command2[0] = ft_strjoin("/usr/bin/", command2[0]);



    char *envp[] = { "PATH=/bin:/usr/bin", NULL };

    int fd[2];
    if (pipe(fd) == -1)
        return 1;

    int id0 = fork();
    if (id0 == -1)
        return 2;
    if (id0 == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(command1[0], command1, envp);
    }
    int id1 = fork();
    if (id1 == -1)
        return 3;
    if (id1 == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execve(command2[0], command2, envp);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(id0, NULL, 0);
    waitpid(id1, NULL, 0);
    return 0;
}
