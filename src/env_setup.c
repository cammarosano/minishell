/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:06:14 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 18:06:15 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	**env_copy_error(char **envp)
{
	ft_perror("copy_env");
	if (envp)
		ft_free_split(envp);
	return (NULL);
}

char	**copy_env(char **envp)
{
	int		i;
	int		n;
	char	**shell_envp;
	int		len;

	n = 0;
	while (envp[n])
		n++;
	shell_envp = malloc(sizeof(*shell_envp) * (n + 1));
	if (!shell_envp)
		return (env_copy_error(shell_envp));
	i = -1;
	while (++i < n)
	{
		len = ft_strlen(envp[i]);
		shell_envp[i] = malloc(sizeof(char) * (len + 1));
		if (!shell_envp[i])
			return (env_copy_error(shell_envp));
		ft_strlcpy(shell_envp[i], envp[i], len + 1);
	}
	shell_envp[n] = NULL;
	return (shell_envp);
}

// increment SHLVL variable, or set it to 1 if inexistant.
// returns 0 upon success, -1 if error.
int	increment_shlvl(t_sh_env *shell_env)
{
	int		lvl;
	char	*lvl_str;
	int		ret;

	lvl_str = expand_var(shell_env->envp, "SHLVL");
	if (!lvl_str || !*lvl_str)
		return (set_var(shell_env, "SHLVL", "1"));
	lvl = ft_atoi(lvl_str);
	if (lvl < 9 && ft_isdigit(*lvl_str))
	{
		lvl_str[0] += 1;
		lvl_str[1] = '\0';
		return (0);
	}	
	lvl_str = ft_itoa(lvl + 1);
	if (!lvl_str)
		return (ft_perror_ret("ft_itoa", -1));
	ret = set_var(shell_env, "SHLVL", lvl_str);
	free(lvl_str);
	return (ret);
}

/*
makes a copy of the environment
increments the SHLVL variable (an error here is non-fatal)
sets the "?" special variable to 0
removes OLDPWD variable
*/
int	setup_env(t_sh_env *shell_env, char **envp)
{
	shell_env->envp = copy_env(envp);
	if (!shell_env->envp)
		return (-1);
	if (increment_shlvl(shell_env) == -1)
	{
		ft_free_split(shell_env->envp);
		return (-1);
	}
	remove_var("OLDPWD", shell_env);
	shell_env->question_mark = 0;
	return (0);
}
