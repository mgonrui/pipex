/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:31:14 by mariogo2          #+#    #+#             */
/*   Updated: 2025/05/02 19:40:35 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	free_double_ptr(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	open_files_check(char **argv)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
		ft_error("open infile failed\n", true);
	outfile_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	if (outfile_fd == -1)
	{
		close(infile_fd);
		ft_error("open outfile failed\n", true);
	}
	close(infile_fd);
	close(outfile_fd);
	return ;
}

char	*get_path_variable(char **envp)
{
	int		i;
	char	*variable;

	i = 0;
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

char	*ret_path_if_exists(char **list_of_paths, char *program_name)
{
	int		i;
	char	*program_path;
	char	*temp;

	i = 0;
	while (list_of_paths[i] != NULL)
	{
		temp = ft_strjoin(list_of_paths[i], "/");
		program_path = ft_strjoin(temp, program_name);
		free(temp);
		if (!access(program_path, X_OK))
			return (program_path);
		free(program_path);
		i++;
	}
	return (NULL);
}

int	get_cmd_path(char **envp, char **binpath, char ***cmd, char *argv)
{
	char	**list_of_paths;
	char	*single_line_path;

	single_line_path = get_path_variable(envp);
	if (single_line_path == NULL)
		return (ft_error("Did not find any PATH\n", false), 1);
	list_of_paths = ft_split(single_line_path, ':');
	if (list_of_paths == NULL)
		return (ft_error("Memory allocation failure\n", false), 2);
	*cmd = ft_split(argv, ' ');
	if (*cmd == NULL)
		return (ft_error("Memory allocation failure\n", false), 3);
	*binpath = ret_path_if_exists(list_of_paths, *cmd[0]);
	free_double_ptr((void **)list_of_paths);
	if (*binpath == NULL)
		return (ft_error("Executable not found\n", false), 4);
	return (0);
}
