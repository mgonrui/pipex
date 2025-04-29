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

void in_child_proc(int *fd, char *binpath, char **cmd1, char **envp, char *fil)
{
    int in_file_fd;

    in_file_fd = open(fil, O_RDONLY);
    dup2(in_file_fd, STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    close(in_file_fd);
    execve(binpath, cmd1, envp);
}

void out_child_proc(int *fd, char *binpath, char **cmd2, char **envp, char *fil)
{
    int out_file_fd;

    out_file_fd = open(fil, O_WRONLY | O_TRUNC);
    dup2(out_file_fd, STDOUT_FILENO);
    dup2(fd[0], STDIN_FILENO);
    close(fd[1]);
    close(fd[0]);
    close(out_file_fd);
    execve(binpath, cmd2, envp);
}

int main(int argc, char **argv, char **envp)
{
    char **cmd1;
    char **cmd2;
    char *binpaths[2];
    int fd[2];
    int id[2];

    if (argc != 5)
        ft_error("Wrong number of args\n", true);
    open_files_check(argv);
    if (get_cmd_path(envp, &binpaths[0], &cmd1, argv[2]) != 0)
        return free_all(binpaths, cmd1, cmd2, true), 0;
    if(get_cmd_path(envp, &binpaths[1], &cmd2, argv[3]) != 0)
        return free_all(binpaths, cmd1, cmd2, false), 0;
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
    return cleanup(id, fd, binpaths, cmd1, cmd2), 0;
}
