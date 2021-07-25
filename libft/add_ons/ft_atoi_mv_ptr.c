/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mv_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:47:19 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:45:05 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_ons.h"

static void	check_overflow(long *nbr)
{
	if (*nbr > INT_MAX)
		*nbr = INT_MAX;
	else if (*nbr < INT_MIN)
		*nbr = INT_MIN;
}

int	ft_atoi_mv_ptr(char **ptr)
{
	long	nbr;
	int		sign;

	while (ft_isspace(**ptr))
		(*ptr)++;
	sign = 1;
	if (**ptr == '+' || **ptr == '-')
	{
		if (**ptr == '-')
			sign = -1;
		(*ptr)++;
	}
	nbr = 0;
	while (**ptr >= '0' && **ptr <= '9')
	{
		nbr = nbr * 10 + sign * (**ptr - '0');
		check_overflow(&nbr);
		(*ptr)++;
	}
	return (nbr);
}
