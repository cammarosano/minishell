/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_echo_pwd_unset.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:54:15 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 17:54:16 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	builtin_env(char **argv, t_sh_env *shell_env)
{
	int		i;
	char	**envp;

	(void)argv;
	envp = shell_env->envp;
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], 1);
	return (0);
}

int	builtin_echo(char **argv, t_sh_env *shell_env)
{
	int	n_flag;
	int	i;

	(void)shell_env;
	n_flag = 0;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		n_flag = 1;
	i = 1 + n_flag;
	while (argv[i])
	{
		if (i > 1 + n_flag)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (0);
}

// it does not rely on PWD env variable (like bash also does not)
int	builtin_pwd(char **argv, t_sh_env *shell_env)
{
	char	*pwd;

	(void)argv;
	(void)shell_env;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_perror_ret("pwd", 1));
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int	builtin_unset(char **argv, t_sh_env *shell_env)
{
	int	i;
	int	ret_value;

	i = 0;
	ret_value = 0;
	while (argv[++i])
	{
		if (is_valid_name(argv[i]))
			remove_var(argv[i], shell_env);
		else
		{
			print_error_msg_name(argv[i], "unset");
			ret_value = 1;
		}
	}
	return (ret_value);
}
