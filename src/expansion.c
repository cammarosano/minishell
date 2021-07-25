/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:12:42 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/03 15:12:43 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// appends str2 to str1. The sources are freed (so they must be mallocd memory).
// NULL + str2 = str2 (even if str is NULL)
// if error, returns NULL
// obs: ft_strjoin is protected, and returns NULL in case of error.
static char	*append(char *str1, char *str2)
{
	char	*dst;

	if (!str1)
		return (str2);
	dst = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (dst);
}

// makes a copy of chars up to DOLLAR_SIGN or '\0'
// *str is moved to '\0' or DOLLAR_SIGN
static char	*get_chars_part(char **str)
{
	int		len;
	char	*ptr;
	char	*dst;

	ptr = *str;
	len = 0;
	while (**str && **str != DOLLAR_SIGN)
	{
		len++;
		(*str)++;
	}
	dst = ft_substr(ptr, 0, len);
	if (!dst)
		return (NULL);
	return (dst);
}

// moves *str to char after var_name
// returns a newly mallocd string containing the value of var
// if var has no valid name of if it does no exist, returns the empty string.
// NULL if error.
static char	*get_var_value_part(char **str, t_sh_env *shell_env)
{
	char	*var_name;
	char	*var_value;

	(*str)++;
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(shell_env->question_mark));
	}
	var_name = parse_var_name(str);
	if (!var_name || !*var_name)
		return (var_name);
	var_value = expand_var(shell_env->envp, var_name);
	free(var_name);
	if (!var_value)
		return (ft_strdup(""));
	return (ft_strdup(var_value));
}

static char	*free_return_null(char *str)
{
	free(str);
	return (NULL);
}

// expands all DOLLAR_SIGN-VAR_NAME occurrences into their respective values
// returns a freeable str or NULL if error
char	*expand_str(char *str, t_sh_env *shell_env)
{
	char	*dst;
	char	*chars_part;
	char	*var_value_part;

	dst = NULL;
	while (*str)
	{
		if (*str == DOLLAR_SIGN)
		{
			var_value_part = get_var_value_part(&str, shell_env);
			if (!var_value_part)
				return (free_return_null(dst));
			dst = append(dst, var_value_part);
			if (!dst)
				return (NULL);
			continue ;
		}
		chars_part = get_chars_part(&str);
		if (!chars_part)
			return (free_return_null(dst));
		dst = append(dst, chars_part);
		if (!dst)
			return (NULL);
	}
	return (dst);
}
