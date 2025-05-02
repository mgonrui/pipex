/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:39:39 by mariogo2          #+#    #+#             */
/*   Updated: 2025/05/02 20:16:54 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	in_child_proc(int *fd, char *fil)
{
	int	in_file_fd;

	in_file_fd = open(fil, O_RDONLY);
	dup2(in_file_fd, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(in_file_fd);
}

void	out_child_proc(int *fd, char *fil)
{
	int	out_file_fd;

	out_file_fd = open(fil, O_WRONLY | O_TRUNC);
	dup2(out_file_fd, STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	close(out_file_fd);
}

void	check_paths(char **envp, char **binpaths, char ***cmds, char **argv)
{
	if (get_cmd_path(envp, &binpaths[0], &cmds[0], argv[2]) != 0)
	{
		free_all(binpaths, cmds[0], cmds[1], true);
		exit(1);
	}
	if (get_cmd_path(envp, &binpaths[1], &cmds[1], argv[3]) != 0)
	{
		free_all(binpaths, cmds[0], cmds[1], false);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**cmds[2];
	char	*binpaths[2];
	int		fd[2];
	int		id[2];

	if (argc != 5)
		ft_error("Wrong number of args\n", true);
	open_files_check(argv);
	check_paths(envp, binpaths, cmds, argv);
	if (pipe(fd) == -1)
		return (1);
	id[0] = safe_fork(id[0]);
	if (id[0] == 0)
	{
		in_child_proc(fd, argv[1]);
		execve(binpaths[0], cmds[0], envp);
	}
	id[1] = safe_fork(id[1]);
	if (id[1] == 0)
	{
		out_child_proc(fd, argv[4]);
		execve(binpaths[1], cmds[1], envp);
	}
	return (cleanup(id, fd, binpaths, cmds), 0);
}
