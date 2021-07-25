/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:49:47 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/30 15:37:49 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!src)
		return (0);
	i = 0;
	if (dst)
	{
		while (dstsize > 1 && *src)
		{
			*dst++ = *src++;
			i++;
			dstsize--;
		}
		if (dstsize)
			*dst = '\0';
	}
	while (*src++)
		i++;
	return (i);
}
