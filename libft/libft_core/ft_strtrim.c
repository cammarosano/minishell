/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:28:18 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:10:28 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, const char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static int	get_size(char const *s1, const char *set)
{
	int	i;
	int	size;

	while (*s1 && isinset(*s1, set))
		s1++;
	i = 0;
	size = 0;
	while (*s1)
	{
		if (!isinset(*s1, set))
			size = i + 1;
		i++;
		s1++;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		size;
	char	*str;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	size = get_size(s1, set);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	ptr = str;
	while (isinset(*s1, set))
		s1++;
	while (size--)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (str);
}
