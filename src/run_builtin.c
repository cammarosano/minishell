/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:39:37 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/03 15:39:38 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// duplicates the file descriptors 0, 1 and 2, to be recovered later.
int	backup_std_fds(int *fd)
{
	int	i;

	i = 0;
	while (i <= 2)
	{
		fd[i] = dup(i);
		if (fd[i] == -1)
		{
			ft_perror("dup");
			while (--i >= 0)
				close(fd[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

// restores stdin, stdout and stderr to the original file descriptors (0, 1, 2)
int	restore_std_fds(int *fd)
{
	int	i;
	int	ret_value;

	ret_value = 0;
	i = 0;
	while (i <= 2)
	{
		if (dup2(fd[i], i) == -1)
		{
			ft_perror("dup2");
			ret_value = -1;
		}
		close(fd[i]);
		i++;
	}
	return (ret_value);
}

// retuns index (0 to 6) if the command is a builtin, -1 otherwise
int	is_builtin(char *command_name)
{
	static char	*builtin[7] = {"echo", "cd", "pwd", "export", "unset",
	"env", "exit"};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(command_name, builtin[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

// jump table to call builtin command (array of pointers to functions)
// indexes must match those in is_builtin()
int	call_builtin(int builtin_index, char **argv, t_sh_env *shell_env)
{
	static	int	(*f[7])(char **, t_sh_env *) = {builtin_echo, builtin_cd,
	builtin_pwd, builtin_export, builtin_unset, builtin_env, builtin_exit};

	return (f[builtin_index](argv, shell_env));
}

// makes redirections, calls builtin function and restores the fds.
// returns the return value of the builtin, or -1 if error related
// to the redirections.
int	run_builtin(int builtin_index, t_command *command, t_sh_env *shenv)
{
	int	back_up_fds[3];
	int	ret;

	if (backup_std_fds(back_up_fds) == -1)
		return (-1);
	if (process_redirections_list(command->redirections) == -1)
	{
		restore_std_fds(back_up_fds);
		return (-1);
	}
	ret = call_builtin(builtin_index, command->argv, shenv);
	if (restore_std_fds(back_up_fds) == -1)
		return (-1);
	return (ret);
}
