/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 14:59:31 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/20 17:22:15 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ptr;

	str = malloc(sizeof(*str) * (ft_strlen(s1) + 1));
	if (!str)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ptr = str;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (str);
}
