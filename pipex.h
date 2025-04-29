/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42mala...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:40:00 by mariogo2          #+#    #+#             */
/*   Updated: 2025/02/02 14:40:01 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
#define PIPEX_H


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../libft/libft.h"

void free_double_ptr(void **ptr);
char *ret_path_if_exists(char **path, char *program);
char *get_path_variable(char **envp);
void open_files_check(char **argv);
void get_cmd_path(char **envp, char **binfile, char ***cmd, char *argv);
void ft_error_exit(char *str, int errorcode);

#endif // PIPEX_H
