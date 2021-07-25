/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:50:04 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 15:31:51 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// if path is NULL, expands the HOME variable. If it is non-existant,
// returns NULL.
static char	*resolve_path_cd(char *path, t_sh_env *shenv)
{
	if (path)
		return (path);
	path = expand_var(shenv->envp, "HOME");
	if (!path)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	return (path);
}

// updates the OLD_PWD and PWD env variables.
// Return 1 if any error occured, 0 otherwise.
static int	set_pwd_oldpwd_vars(char *old_pwd, t_sh_env *shenv)
{
	char	*pwd;
	int		ret;

	ret = 0;
	if (!old_pwd || set_var(shenv, "OLDPWD", old_pwd) == -1)
		ret = 1;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_perror("getcwd");
	if (!pwd || set_var(shenv, "PWD", pwd) == -1)
		ret = 1;
	free(pwd);
	return (ret);
}

// errors from getcwd are considered non-fatal (cd returns 1 in this case)
int	builtin_cd(char **argv, t_sh_env *shell_env)
{
	char	*path;
	char	*old_pwd;
	int		ret;

	path = resolve_path_cd(argv[1], shell_env);
	if (!path)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		ft_perror("getcwd");
	if (chdir(path) == -1)
	{
		free(old_pwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_perror(path);
		return (1);
	}
	ret = set_pwd_oldpwd_vars(old_pwd, shell_env);
	free(old_pwd);
	return (ret);
}
