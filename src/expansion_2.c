/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:12:52 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 15:12:40 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// returns the variable name in a freeable string moves pointer to first char
// after name.
// returns NULL if error. 
// if the first characted is not_valid, the returned name will be the empty
// string and the pointer will be moved to the next char (if not \0).
char	*parse_var_name(char **str)
{
	int		len;
	char	*ptr;

	ptr = *str;
	if (!(ft_isalpha(**str) || **str == '_'))
	{
		if (**str)
			(*str)++;
		return (ft_strdup(""));
	}
	(*str)++;
	len = 1;
	while (ft_isalnum(**str) || **str == '_')
	{
		(*str)++;
		len++;
	}
	return (ft_substr(ptr, 0, len));
}

static int	contains_dollar(char *str)
{
	while (*str)
	{
		if (*str == DOLLAR_SIGN)
			return (1);
		str++;
	}
	return (0);
}

// check for DOLLAR_SIGN in every word, and replace word by another one
// with the expanded variable
// Returns -1 if error, 0 upon success.
int	make_var_expansions_args(char **argv, t_sh_env *shell_env)
{
	char	*new_arg;

	while (*argv)
	{
		if (contains_dollar(*argv))
		{
			new_arg = expand_str(*argv, shell_env);
			if (!new_arg)
				return (-1);
			free(*argv);
			*argv = new_arg;
		}
		argv++;
	}
	return (0);
}

int	make_var_expansions_redirs(t_list *redirs_lst, t_sh_env *shenv)
{
	t_redir	*red;
	char	*new_str;

	while (redirs_lst)
	{
		red = redirs_lst->content;
		if (contains_dollar(red->file))
		{
			new_str = expand_str(red->file, shenv);
			if (!new_str)
				return (-1);
			free(red->file);
			red->file = new_str;
		}
		redirs_lst = redirs_lst->next;
	}
	return (0);
}

int	make_var_expansions(t_command *command, t_sh_env *shenv)
{
	if (make_var_expansions_args(command->argv, shenv) == -1)
		return (-1);
	if (make_var_expansions_redirs(command->redirections, shenv) == -1)
		return (-1);
	return (0);
}
