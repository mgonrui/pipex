/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42mala...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:39:39 by mariogo2          #+#    #+#             */
/*   Updated: 2025/02/05 19:43:49 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int get_cmd(char **envp, char **binfile, char ***cmd, char *argv)
{
    char **path;
    path = ft_split(get_path(envp), ':');
    *cmd = ft_split(argv, ' ');
    *binfile = path_exists(path, *cmd[0]);
    free_double_ptr((void **)path);
    if (binfile == NULL)
    {
        perror("Did not find the path to the first cmd\n");
        exit(1);
    }
    return 0;
}

void cleanup(int *id, int *fd, char **binfile, char **cmd1, char **cmd2)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(id[0], NULL, 0);
    waitpid(id[1], NULL, 0);
    free(binfile[0]);
    free(binfile[1]);
    free_double_ptr((void **)cmd1);
    free_double_ptr((void **)cmd2);
}

int in_child_proc(int *fd, char **binfile, char **cmd1, char **envp)
{
    int in_file_fd;
    in_file_fd = open("infile", O_RDONLY);
    dup2(in_file_fd, STDIN_FILENO);
    close(in_file_fd);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(binfile[0], cmd1, envp);
    exit(1);
}

int out_child_proc(int *fd, char **binfile, char **cmd2, char **envp)
{
    int out_file_fd;
    out_file_fd = open("outfile", O_WRONLY | O_TRUNC);
    dup2(out_file_fd, STDOUT_FILENO);
    close(out_file_fd);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execve(binfile[1], cmd2, envp);
    exit(2);
}

int main(int argc, char **argv, char **envp)
{
    char **cmd1;
    char **cmd2;
    char *binfile[2];
    int fd[2];
    int id[2];

    get_cmd(envp, &binfile[0], &cmd1, argv[2]);
    get_cmd(envp, &binfile[1], &cmd2, argv[3]);
    if (argc < 5)
        return (perror("Wrong number of args"), 0);
    if (pipe(fd) == -1)
        return 1;
    id[0] = fork();
    if (id[0] == -1)
        return 2;
    if (id[0] == 0)
        in_child_proc(fd, binfile, cmd1, envp);
    id[1] = fork();
    if (id[1] == -1)
        return 3;
    if (id[1] == 0)
        out_child_proc(fd, binfile, cmd2, envp);
    cleanup(id, fd, binfile, cmd1, cmd2);
    return 0;
}
