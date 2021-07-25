/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 20:54:29 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/24 20:55:00 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	parse_fd(char **ptr)
{
	int	fd;

	if (**ptr == LESS_THAN)
		fd = 0;
	else if (**ptr == GREATER_THAN)
		fd = 1;
	else
		fd = ft_atoi_mv_ptr(ptr);
	return (fd);
}

int	parse_redir_op(char **ptr)
{
	int	op;

	if (**ptr == LESS_THAN)
	{
		(*ptr)++;
		if (**ptr == LESS_THAN)
		{
			(*ptr)++;
			op = re_heredoc;
		}
		else
			op = re_input;
	}
	else
	{
		(*ptr)++;
		if (**ptr == GREATER_THAN)
		{
			(*ptr)++;
			op = re_output_append;
		}
		else
			op = re_output;
	}
	return (op);
}

int	parse_filename(char **file, char *str, char **arg)
{
	if (*str)
	{
		*file = ft_strdup(str);
		if (!*file)
			return (-1);
		return (0);
	}
	remove_arg_from_argv(arg);
	if (!*arg)
	{
		ft_putendl_fd("Syntax error", 2);
		return (-1);
	}
	*file = ft_strdup(*arg);
	if (!*file)
		return (-1);
	return (0);
}

//  [n]<file [n]>file [n]>>file
// parses redirection params and REMOVES arg from argv
t_redir	*str2redir_struct(char **arg)
{
	t_redir	*red;
	char	*str;

	str = *arg;
	red = malloc(sizeof(*red));
	if (!red)
		return (NULL);
	red->n = parse_fd(&str);
	red->op = parse_redir_op(&str);
	if (parse_filename(&red->file, str, arg) == -1)
	{
		free(red);
		return (NULL);
	}
	remove_arg_from_argv(arg);
	return (red);
}
