/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:01:17 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 12:38:38 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int	digits;

	digits = 1;
	if (n < 0)
		digits = 2;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	size = get_size(n);
	str = malloc(sizeof(*str) * (size + 1));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	while (n >= 10 || n <= -10)
	{
		str[size--] = (n % 10) * sign + '0';
		n /= 10;
	}
	str[size--] = (n % 10) * sign + '0';
	if (sign == -1)
		str[size] = '-';
	return (str);
}
