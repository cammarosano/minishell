/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:15:12 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 15:05:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	init_shell(char **envp, t_sh_env *shenv)
{
	setup_signal_handlers();
	if (setup_env(shenv, envp) == -1)
		return (-1);
	shenv->pipeline = NULL;
	shenv->hd_files = NULL;
	return (0);
}

// Prompts user for input
// Returns a freeable string containing the user input,
// which is added to history
// Empty lines are discarded and prompt is shown again
// ctrl-D on a empty line (or malloc error) makes program exit.
char	*get_command(t_sh_env *shell_env)
{
	char	*line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			write(1, "\n", 1);
			ft_free_split(shell_env->envp);
			exit(shell_env->question_mark);
		}
		if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		return (line);
	}
}

// interpret symbols in a line and return the pipeline as list of t_commands
t_list	*parse_line(char *line)
{
	t_list	*pipeline;
	char	*processed_line;

	processed_line = pre_processor(line);
	if (!processed_line)
		return (NULL);
	pipeline = split_by_pipe(processed_line);
	free(processed_line);
	return (pipeline);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_sh_env	shell_env;

	if (init_shell(envp, &shell_env) == -1)
		return (1);
	while (19)
	{
		line = get_command(&shell_env);
		shell_env.pipeline = parse_line(line);
		free(line);
		shell_env.question_mark = execute_line(&shell_env);
		ft_lstclear(&shell_env.hd_files, delete_file);
		ft_lstclear(&shell_env.pipeline, clear_command);
	}
	(void)argc;
	(void)argv;
}
