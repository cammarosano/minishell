/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:54:31 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 15:11:07 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	clear_redirection(void *ptr)
{
	t_redir	*redir;

	redir = ptr;
	free(redir->file);
	free(redir);
}

void	clear_command(void *ptr)
{
	t_command	*command;

	command = ptr;
	ft_free_split(command->argv);
	ft_lstclear(&command->redirections, clear_redirection);
	free(command);
}

// frees memory:
// envp (array of strings)
// pipeline (list of t_commands)
void	clear_memory(t_sh_env *shell_env)
{
	ft_free_split(shell_env->envp);
	ft_lstclear(&shell_env->hd_files, delete_file);
	ft_lstclear(&shell_env->pipeline, clear_command);
}

int	clear_mem_exit(t_sh_env *shell_env, int exit_code)
{
	clear_memory(shell_env);
	exit (exit_code);
}

void	delete_file(void *file_name)
{
	unlink((char *)file_name);
}
