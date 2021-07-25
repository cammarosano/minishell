/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:53:29 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 17:53:30 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_valid_name(char *var)
{
	if (!(ft_isalpha(*var) || *var == '_'))
		return (0);
	var++;
	while (*var && *var != '=')
	{
		if (!(ft_isalnum(*var) || *var == '_'))
			return (0);
		var++;
	}
	return (1);
}

void	print_error_msg_name(char *arg, char *builtin)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	export_no_args(t_sh_env *shenv)
{
	int		i;
	char	**envp;
	char	*ptr;

	envp = shenv->envp;
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ptr = envp[i];
		while (*ptr && *ptr != '=')
			ft_putchar_fd(*ptr++, 1);
		if (ptr)
			printf("=\"%s\"\n", ++ptr);
		else
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}

static int	export_var(char *arg, t_sh_env *shenv)
{
	char	*var_name;
	char	*var_value;
	int		ret;

	var_name = parse_var_name(&arg);
	if (!var_name)
		return (-1);
	var_value = arg + 1;
	ret = set_var(shenv, var_name, var_value);
	free(var_name);
	return (ret);
}

// for now, only name=value will take effect ("export name" does nothing)
int	builtin_export(char **argv, t_sh_env *shell_env)
{
	int		i;
	int		return_value;

	if (!argv[1])
		return (export_no_args(shell_env));
	return_value = 0;
	i = 0;
	while (argv[++i])
	{
		if (!is_valid_name(argv[i]))
		{
			print_error_msg_name(argv[i], "export");
			return_value = 1;
			continue ;
		}
		if (!ft_strchr(argv[i], '='))
			continue ;
		if (export_var(argv[i], shell_env) == -1)
			return_value = 1;
	}
	return (return_value);
}
