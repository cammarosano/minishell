/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:31:48 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 18:31:49 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// returns of index of the envp array in which var can be found,
// or -1 if not found.
int	find_var_index(char **envp, char *var)
{
	int	i;
	int	name_len;

	name_len = ft_strlen(var);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, name_len) == 0 && envp[i][name_len] == '=')
			return (i);
	}
	return (-1);
}

// returns pointer to var's first char after "=", or NULL if var not found
// no memory allocation
char	*expand_var(char **envp, char *var)
{
	int		name_len;
	int		var_index;

	var_index = find_var_index(envp, var);
	if (var_index == -1)
		return (NULL);
	name_len = ft_strlen(var);
	return (envp[var_index] + name_len + 1);
}

// if var_name exists in envp, the string is freed and all contents to its right
// are shift 1 position to the left (so, no reallocation)
void	remove_var(char *var_name, t_sh_env *shell_env)
{
	int		i;
	char	**envp;

	envp = shell_env->envp;
	i = find_var_index(envp, var_name);
	if (i == -1)
		return ;
	free(envp[i]);
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
}
