/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:25:49 by mariogo2          #+#    #+#             */
/*   Updated: 2025/05/02 20:25:57 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	safe_fork(int id)
{
	id = fork();
	if (id == -1)
		ft_error("Fork failure\n", true);
	return (id);
}

void	free_all(char **binpaths, char **cmd1, char **cmd2,
		bool free_first_only)
{
	if (free_first_only == false)
	{
		free(binpaths[1]);
		free_double_ptr((void **)cmd2);
	}
	free(binpaths[0]);
	free_double_ptr((void **)cmd1);
}

void	cleanup(int *id, int *fd, char **binpaths, char ***cmds)
{
	close(fd[0]);
	close(fd[1]);
	waitpid(id[0], NULL, 0);
	waitpid(id[1], NULL, 0);
	free_all(binpaths, cmds[0], cmds[1], false);
}

void	ft_error(char *str, bool exit_program)
{
	int	i;

	i = 0;
	write(2, "Error: ", 8);
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	if (exit_program == true)
		exit(1);
}
