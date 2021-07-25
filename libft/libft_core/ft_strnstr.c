/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:43:37 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 12:40:01 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cmp_str(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (0);
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;

	len_needle = ft_strlen(needle);
	if (!len_needle)
		return ((char *)haystack);
	while (*haystack && len >= len_needle)
	{
		if (cmp_str(haystack, needle))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
