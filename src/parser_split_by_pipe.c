/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split_by_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 20:53:37 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/24 20:56:41 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// Split a command string into its separate words and store it in a 
// t_command struct.
// A command argv of size zero (after removing redirections) is considered
// a syntax error.
t_command	*command_string2struct(char *cmd_str)
{
	t_command	*command;

	command = malloc(sizeof(*command));
	if (!command)
		return (NULL);
	command->argv = ft_split(cmd_str, SPACEBAR);
	if (!command->argv)
	{
		free(command);
		return (NULL);
	}
	if (parse_redirections(command) == -1)
	{
		ft_free_split(command->argv);
		free (command);
		return (NULL);
	}
	if (command->argv[0] == NULL)
	{
		ft_putendl_fd("Syntax error", 2);
		clear_command(command);
		return (NULL);
	}
	return (command);
}

int	add_cmd_2_list(t_list **lst, char *cmd_str)
{
	t_command	*cmd_struct;
	t_list		*elem;

	cmd_struct = command_string2struct(cmd_str);
	if (!cmd_struct)
		return (-1);
	elem = ft_lstnew(cmd_struct);
	if (!elem)
	{
		clear_command(cmd_struct);
		return (-1);
	}
	ft_lstadd_back(lst, elem);
	return (0);
}

// compares the the number of elements resulting from the split against the
// number of "|"s. Detects a pipe at beggining or end of the cmd line, as well
// as a "||".
static int	validate_split(char **argv, char *line)
{
	int	argv_count;
	int	pipe_count;

	argv_count = 0;
	while (argv[argv_count])
		argv_count++;
	pipe_count = 0;
	while (*line)
	{
		if (*line == PIPE)
			pipe_count++;
		line++;
	}
	if (argv_count != pipe_count + 1)
		return (0);
	return (1);
}

static char	**split(char *line)
{
	char	**commands;

	commands = ft_split(line, PIPE);
	if (!commands)
		return (NULL);
	if (!validate_split(commands, line))
	{
		ft_putendl_fd("Syntax error", 2);
		ft_free_split(commands);
		return (NULL);
	}
	return (commands);
}

// split a line by "|"
// returns a list of t_commands, or NULL if error.
t_list	*split_by_pipe(char *line)
{
	t_list	*lst;
	char	**commands;
	int		i;

	commands = split(line);
	if (!commands)
		return (NULL);
	lst = NULL;
	i = 0;
	while (commands[i])
	{
		if (add_cmd_2_list(&lst, commands[i]) == -1)
		{
			ft_lstclear(&lst, clear_command);
			break ;
		}
		i++;
	}
	ft_free_split(commands);
	return (lst);
}
