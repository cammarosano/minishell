/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:01:12 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 18:59:56 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	exit_code_from_child(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Quit", 1);
		return (128 + WTERMSIG(status));
	}
	return (0);
}

// function to be called by the main (parent) process.
// makes variable expansions, checks if command is a builtin
// if builtin, calls run_builtin
// else, forks into a subshell, which calls exec_bin
// the return code for the command (builtin or not) is returned, or
// -1 if error.
int	run_simple_command(t_command *command, t_sh_env *shenv)
{
	int		builtin_index;
	int		status;
	pid_t	id;

	if (make_var_expansions(command, shenv) == -1)
		return (-1);
	builtin_index = is_builtin(command->argv[0]);
	if (builtin_index != -1)
		return (run_builtin(builtin_index, command, shenv));
	id = fork();
	if (id == 0)
		exec_bin(command, shenv);
	wait(&status);
	return (exit_code_from_child(status));
}

// executes pipeline
// A pipeline of size 1 is run by run_simple_command.
// Otherwise, by run_pipeline.
int	execute_line(t_sh_env *shell_env)
{
	t_list	*pipeline;
	int		n_commands;
	int		ret;

	pipeline = shell_env->pipeline;
	n_commands = ft_lstsize(pipeline);
	if (n_commands == 0)
		return (1);
	if (get_here_docs(pipeline, &shell_env->hd_files) == 1)
		return (1);
	if (n_commands == 1)
		ret = run_simple_command(pipeline->content, shell_env);
	else
		ret = run_pipeline(pipeline, shell_env, n_commands);
	if (ret == -1)
		ret = 1;
	return (ret);
}
