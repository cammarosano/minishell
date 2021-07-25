/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 13:54:43 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:10:58 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ptr_dst;
	const char	*ptr_src;

	if (!dst && !src)
		return (NULL);
	ptr_dst = dst;
	ptr_src = src;
	while (n--)
		*ptr_dst++ = *ptr_src++;
	return (dst);
}
