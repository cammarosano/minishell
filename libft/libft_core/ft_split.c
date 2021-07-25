/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:54:02 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:08:16 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}

static char const	*get_next_word(char const *ptr, char c)
{
	while (*ptr && *ptr == c)
		ptr++;
	return (ptr);
}

static int	count_words(char const *s, char c)
{
	int			count;
	char const	*ptr;

	count = 0;
	ptr = get_next_word(s, c);
	while (*ptr)
	{
		count++;
		while (*ptr && *ptr != c)
			ptr++;
		ptr = get_next_word(ptr, c);
	}
	return (count);
}

static int	wordlen(char const *ptr, char c)
{
	int	len;

	len = 0;
	while (*ptr && *ptr != c)
	{
		len++;
		ptr++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	char	*ptr;
	int		i;
	int		n;

	if (!s)
		return (NULL);
	n = count_words(s, c);
	array = malloc(sizeof(*array) * (n + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (++i < n)
	{
		s = get_next_word(s, c);
		array[i] = malloc(sizeof(*(array[i])) * (wordlen(s, c) + 1));
		if (!array[i])
			return (free_array(array));
		ptr = array[i];
		while (*s && *s != c)
			*ptr++ = *s++;
		*ptr = '\0';
	}
	array[i] = NULL;
	return (array);
}
