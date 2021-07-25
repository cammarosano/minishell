/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 20:20:00 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:34:39 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_set_null(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (-1);
}

size_t	line_len(char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0' && *str != '\n' && *str != -1)
	{
		str++;
		len++;
	}
	return (len);
}

char	*join(char *s1, char *s2)
{
	char	*str;
	char	*dest;
	char	*src;

	str = malloc(sizeof(char) * (line_len(s1) + line_len(s2) + 1));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	dest = str;
	src = s1;
	while (*src)
		*dest++ = *src++;
	src = s2;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	free(s1);
	free(s2);
	return (str);
}

void	mem_shift(char *buffer, size_t i)
{
	char	*src;

	if (buffer[i] == '\0' || buffer[i] == -1)
		buffer[0] = '\0';
	else
	{
		src = buffer + i + 1;
		while (*buffer != '\0' && *buffer != -1)
			*buffer++ = *src++;
	}
}
