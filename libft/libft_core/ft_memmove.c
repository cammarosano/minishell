/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:33:04 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/30 22:33:21 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*p_dst;
	const char	*p_src;

	if (dst == NULL && src == NULL)
		return (dst);
	p_dst = dst;
	p_src = src;
	if (dst > src)
		while (len--)
			p_dst[len] = p_src[len];
	else
		while (len--)
			*p_dst++ = *p_src++;
	return (dst);
}
