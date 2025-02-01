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
#include <stdbool.h>

int in_child_proc(int *fd, char *bin_file[2], char **command1, char **envp)
{
    int in_file_fd;
    in_file_fd = open("infile", O_RDONLY);
    dup2(in_file_fd, STDIN_FILENO);
    close(in_file_fd);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(bin_file[0], command1, envp);
    exit(1);
}

int out_child_proc(int *fd, char *bin_file[2], char **command2, char **envp)
{
    int out_file_fd;
    out_file_fd = open("outfile", O_WRONLY | O_TRUNC);
    dup2(out_file_fd, STDOUT_FILENO);
    close(out_file_fd);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execve(bin_file[1], command2, envp);
    exit(2);
}


int get_command(char **envp, char **binfile, char ***command, char *argv)
{
    char **path;
    path = ft_split(get_path(envp), ':');
    *command = ft_split(argv, ' ');
    *binfile = path_exists(path, *command[0]);
    free_double_ptr((void **)path);
    if (binfile == NULL)
    {
        perror("Did not find the path to the first command\n");
        exit(1);
    }
    return 0;
}

void cleanup( int *id, int *fd, char *bin_file[2], char **command1, char **command2)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(id[0], NULL, 0);
    waitpid(id[1], NULL, 0);
    free(bin_file[0]);
    free(bin_file[1]);
    free_double_ptr((void **)command1);
    free_double_ptr((void **)command2);
}

int main(int argc, char **argv, char **envp)
{
    char **command1;
    char **command2;
    char *bin_file[2];
    int fd[2];
    int id[2];

    get_command(envp, &bin_file[0], &command1, argv[2]);
    get_command(envp, &bin_file[1], &command2, argv[3]);
    if (argc < 5)
        return (perror("Wrong number of args"), 0);
    if (pipe(fd) == -1)
        return 1;
    id[0] = fork();
    if (id[0] == -1)
        return 2;
    if (id[0] == 0)
        in_child_proc(fd, bin_file, command1, envp);
    id[1] = fork();
    if (id[1] == -1)
        return 3;
    if (id[1] == 0)
        out_child_proc(fd, bin_file, command2, envp);
    cleanup(id, fd, bin_file, command1, command2);
    return 0;
}
