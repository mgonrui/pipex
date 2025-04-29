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

void check_fork_failure(int id)
{
   if (id == -1)
       ft_error_exit("Fork failure\n", 1);
   return ;
}

void cleanup(int *id, int *fd, char **binpaths, char **cmd1, char **cmd2)
{
    close(fd[0]);
    close(fd[1]);
    waitpid(id[0], NULL, 0);
    waitpid(id[1], NULL, 0);
    free(binpaths[0]);
    free(binpaths[1]);
    free_double_ptr((void **)cmd1);
    free_double_ptr((void **)cmd2);
}


void in_child_proc(int *fd, char *binpath, char **cmd1, char **envp, char *fil)
{
    int in_file_fd;
    in_file_fd = open(fil, O_RDONLY);
    dup2(in_file_fd, STDIN_FILENO);
    close(in_file_fd);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    execve(binpath, cmd1, envp);
    exit(EXIT_FAILURE);
}

void out_child_proc(int *fd, char *binpath, char **cmd2, char **envp, char *fil)
{
    int out_file_fd;
    out_file_fd = open(fil, O_WRONLY | O_TRUNC);
    dup2(out_file_fd, STDOUT_FILENO);
    close(out_file_fd);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    execve(binpath, cmd2, envp);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp)
{
    char **cmd1;
    char **cmd2;
    char *binpaths[2];
    int fd[2];
    int id[2];

    if (argc != 5)
        ft_error_exit("Wrong number of args\n", 1);
    open_files_check(argv);
    get_cmd_path(envp, &binpaths[0], &cmd1, argv[2]);
    get_cmd_path(envp, &binpaths[1], &cmd2, argv[3]);
    if (pipe(fd) == -1)
        return 1;
    id[0] = fork();
    check_fork_failure(id[0]);
    if (id[0] == 0)
        in_child_proc(fd, binpaths[0], cmd1, envp, argv[1]);
    id[1] = fork();
    check_fork_failure(id[1]);
    if (id[1] == 0)
        out_child_proc(fd, binpaths[1], cmd2, envp, argv[4]);
    cleanup(id, fd, binpaths, cmd1, cmd2);
    return 0;
}
