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



int main(int argc, char **argv, char **envp)
{
    char **command1;
    char **command2;

    if (argc < 5)
    {
        return 1;
    }

    command1 = ft_split(argv[2], ' ');
    command2 = ft_split(argv[3], ' ');

    command1[0] = ft_strjoin("/usr/bin/", command1[0]);
    command2[0] = ft_strjoin("/usr/bin/", command2[0]);

    int fd[2];
    if (pipe(fd) == -1)
        return 1;

    int id0 = fork();
    if (id0 == -1)
        return 2;
    if (id0 == 0)
    {
        int infile_fd = open("infile", O_RDONLY);
        dup2(infile_fd, STDIN_FILENO);
        close(infile_fd);
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
        int outfile_fd = open("outfile", O_WRONLY | O_TRUNC);
        dup2(outfile_fd, STDOUT_FILENO);
        close(outfile_fd);
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execve(command2[0], command2, envp);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(id0, NULL, 0);
    waitpid(id1, NULL, 0);
    free(command1);
    free(command2);
    return 0;
}
