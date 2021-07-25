/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:51:16 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 17:51:17 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_numeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void	print_error_msg_numeric(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("Minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

static int	error_too_many_args(int return_value)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("Minishell: exit: too many arguments", 2);
	return (return_value);
}

int	builtin_exit(char **argv, t_sh_env *shell_env)
{
	int	exit_code;

	if (argv[1] && argv[2])
		return (error_too_many_args(1));
	if (!argv[1])
		exit_code = shell_env->question_mark;
	else
	{
		if (!is_numeric(argv[1]))
		{
			exit_code = -1;
			print_error_msg_numeric(argv[1]);
		}
		else
			exit_code = ft_atoi(argv[1]);
	}
	clear_memory(shell_env);
	exit(exit_code);
}
