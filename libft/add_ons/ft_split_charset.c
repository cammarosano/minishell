/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:48:21 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:54 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_ons.h"

static int	is_sep(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static char	*get_next_word(char *str, char *charset)
{
	while (*str && is_sep(charset, *str))
		str++;
	return (str);
}

static int	count_words(char *str, char *charset)
{
	int	counter;

	counter = 0;
	str = get_next_word(str, charset);
	while (*str)
	{
		counter++;
		while (*str && !is_sep(charset, *str))
			str++;
		str = get_next_word(str, charset);
	}
	return (counter);
}

static int	word_len(char *word, char *charset)
{
	int	len;

	len = 0;
	while (*word && !is_sep(charset, *word))
	{
		len++;
		word++;
	}
	return (len);
}

char	**ft_split_charset(char *str, char *charset)
{
	char	**array;
	char	*ptr;
	int		n_words;
	int		i;

	if (!str || !charset)
		return (NULL);
	n_words = count_words(str, charset);
	array = malloc(sizeof(*array) * (n_words + 1));
	if (!array)
		return (NULL);
	i = -1;
	while (++i < n_words)
	{
		str = get_next_word(str, charset);
		array[i] = malloc(sizeof(char) * (word_len(str, charset) + 1));
		if (!array[i])
			return (ft_free_split(array));
		ptr = array[i];
		while (*str && !is_sep(charset, *str))
			*ptr++ = *str++;
		*ptr = '\0';
	}
	array[i] = 0;
	return (array);
}
