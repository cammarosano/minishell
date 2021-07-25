/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 20:55:13 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/24 20:56:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	remove_arg_from_argv(char **argv)
{
	int	i;

	i = 0;
	free(argv[i]);
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i++;
	}
}

static int	validate_redir_str(char *str)
{
	while (ft_isdigit(*str))
		str++;
	if (!(*str == GREATER_THAN || *str == LESS_THAN))
	{
		ft_putendl_fd("Syntax error", 2);
		return (0);
	}
	str++;
	if ((*str == GREATER_THAN || *str == LESS_THAN) && (*str != *(str - 1)))
	{
		ft_putendl_fd("Syntax error", 2);
		return (0);
	}
	if (*str++ && *str < 0)
	{
		ft_putendl_fd("Syntax error", 2);
		return (0);
	}
	return (1);
}

static int	parse_str_add2lst(char **arg, t_list **redirs_lst)
{
	t_redir	*red;
	t_list	*lst_node;

	if (!validate_redir_str(*arg))
		return (-1);
	red = str2redir_struct(arg);
	if (!red)
		return (-1);
	lst_node = ft_lstnew(red);
	if (!lst_node)
	{
		clear_redirection(red);
		return (-1);
	}
	ft_lstadd_back(redirs_lst, lst_node);
	return (0);
}

// populates t_command.redirections list
// removes the strings from argv that were related to a redirection
// if error, retuns -1 and redirs list is set to NULL
int	parse_redirections(t_command *cmd)
{
	char	**arg;

	arg = cmd->argv;
	cmd->redirections = NULL;
	while (*arg)
	{
		if (ft_strchr(*arg, LESS_THAN) || ft_strchr(*arg, GREATER_THAN))
		{
			if (parse_str_add2lst(arg, &cmd->redirections) == -1)
			{
				ft_lstclear(&cmd->redirections, clear_redirection);
				return (-1);
			}
		}
		else
			arg++;
	}
	return (0);
}
