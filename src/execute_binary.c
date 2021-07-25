/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:34:29 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 18:34:30 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	print_command_not_found(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
}

static int	resolve_code(char *path)
{
	int	code;

	if (errno == 2)
		code = 127;
	else
		code = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_perror(path);
	return (code);
}

// function to be called by a subshell (child process).
// This function does not return. It exits.
// Resolves the complete path for the command and executes it.
void	exec_bin(t_command *command, t_sh_env *shenv)
{
	int		ret;
	char	*path;
	int		exit_code;

	if (process_redirections_list(command->redirections) == -1)
		clear_mem_exit(shenv, -1);
	ret = resolve_path(command->argv[0], &path, shenv->envp);
	if (ret == -1)
		clear_mem_exit(shenv, -1);
	if (ret == 0)
	{
		print_command_not_found(command->argv[0]);
		clear_mem_exit(shenv, 127);
	}
	execve(path, command->argv, shenv->envp);
	exit_code = resolve_code(path);
	free(path);
	clear_mem_exit(shenv, exit_code);
}
