/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:40:00 by mariogo2          #+#    #+#             */
/*   Updated: 2025/05/02 20:29:30 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

void	free_double_ptr(void **ptr);
char	*ret_path_if_exists(char **path, char *program);
char	*get_path_variable(char **envp);
void	open_files_check(char **argv);
int		get_cmd_path(char **envp, char **binpath, char ***cmd, char *argv);
int		safe_fork(int id);
void	free_all(char **binpaths, char **cmd1, char **cmd2,
			bool free_first_only);
void	cleanup(int *id, int *fd, char **binpaths, char ***cmds);
void	ft_error(char *str, bool exit_program);

#endif // PIPEX_H
