/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:40:18 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/03 15:40:19 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// new_var: pointer to string VAR=VALUE
static int	add_var(t_sh_env *shell_env, char *new_var)
{
	char	**new_envp;
	int		n;
	int		i;

	n = count_vars(shell_env->envp);
	new_envp = malloc(sizeof(*new_envp) * (n + 2));
	if (!new_envp)
		return (-1);
	i = -1;
	while (++i < n)
		new_envp[i] = shell_env->envp[i];
	new_envp[n] = new_var;
	new_envp[n + 1] = NULL;
	free(shell_env->envp);
	shell_env->envp = new_envp;
	return (0);
}

static void	update_var(char **envp, int index, char *new_var)
{
	free(envp[index]);
	envp[index] = new_var;
}

// adds var_name (if non-existant) or updates var_name's value in the
// environment.
// returns 0 upon success, -1 if error 
int	set_var(t_sh_env *shell_env, char *var_name, char *value)
{
	char	*new_var;
	int		size;
	int		index;

	size = ft_strlen(var_name) + ft_strlen(value) + 2;
	new_var = malloc(size);
	if (!new_var)
		return (-1);
	ft_strlcpy(new_var, var_name, size);
	ft_strlcat(new_var, "=", size);
	ft_strlcat(new_var, value, size);
	index = find_var_index(shell_env->envp, var_name);
	if (index == -1)
	{
		if (add_var(shell_env, new_var) == -1)
		{
			free(new_var);
			return (-1);
		}
	}
	else
		update_var(shell_env->envp, index, new_var);
	return (0);
}
