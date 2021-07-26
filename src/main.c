/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:15:12 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/26 16:33:58 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	init_shell(char **envp, t_sh_env *shenv)
{
	if (setup_env(shenv, envp) == -1)
		return (-1);
	shenv->pipeline = NULL;
	shenv->hd_files = NULL;
	return (0);
}

static int	validate_line(char *line)
{
	while (*line)
	{
		if (ft_isprint(*line) && !ft_isspace(*line))
			return (1);
		line++;
	}
	return (0);
}

// Prompts user for input
// Returns a freeable string containing the user input,
// which is added to history
// Empty lines are discarded and prompt is shown again
// ctrl-D on a empty line (or malloc error) makes program exit.
static char	*get_command(t_sh_env *shell_env)
{
	char	*line;

	setup_signal_handlers();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", 1);
			ft_free_split(shell_env->envp);
			exit(shell_env->question_mark);
		}
		if (*line)
			add_history(line);
		if (validate_line(line))
			break ;
		free(line);
	}
	reset_signal_handlers();
	return (line);
}

// interpret symbols in a line and return the pipeline as list of t_commands
static t_list	*parse_line(char *line)
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
