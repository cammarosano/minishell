/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:43:23 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/30 14:53:14 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char		*ptr_dst;

	ptr_src = src;
	ptr_dst = dst;
	while (n--)
	{
		*ptr_dst = *ptr_src;
		if (*ptr_dst == (unsigned char)c)
			return (ptr_dst + 1);
		ptr_src++;
		ptr_dst++;
	}
	return (NULL);
}
