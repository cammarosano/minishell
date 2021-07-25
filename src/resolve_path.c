/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:36:47 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/25 15:10:44 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char	*assemble_path(char *dir, char *file)
{
	char	*str;
	int		size;

	size = ft_strlen(dir) + ft_strlen(file) + 2;
	str = malloc(size);
	if (!str)
		return (NULL);
	ft_strlcpy(str, dir, size);
	ft_strlcat(str, "/", size);
	ft_strlcat(str, file, size);
	return (str);
}

// if bin found, return 1 and path contains the complete path (freeable string)
// if not found, return 0 and path is NULL.
// return -1 if error
static int	lookup_bin(char *command, char **path_dirs, char **path)
{
	int			i;
	struct stat	buf;

	i = 0;
	while (path_dirs[i])
	{
		*path = assemble_path(path_dirs[i], command);
		if (!*path)
			return (ft_perror_ret("assemble_path", -1));
		if (stat(*path, &buf) == 0)
			return (1);
		free(*path);
		i++;
	}
	*path = NULL;
	return (0);
}

// if command contais "/" or if the binary is found in a PATH directory,
// return 1 and a a freeable string to path
// return 0 if binary not found
// return -1 if error
int	resolve_path(char *command, char **path, char **envp)
{
	char		**path_dirs;
	char		*env_path;
	int			ret;

	if (ft_strchr(command, '/'))
	{
		*path = ft_strdup(command);
		if (!*path)
			return (ft_perror_ret("ft_strdup", -1));
		return (1);
	}
	env_path = expand_var(envp, "PATH");
	if (env_path == NULL)
		return (0);
	path_dirs = ft_split(env_path, ':');
	if (!path_dirs)
		return (ft_perror_ret("ft_split", -1));
	ret = lookup_bin(command, path_dirs, path);
	ft_free_split(path_dirs);
	return (ret);
}
