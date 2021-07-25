/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_mv_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:46:41 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:46:22 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_ons.h"

static double	get_int_part(char **ptr)
{
	double	nbr;

	nbr = 0.0;
	while (**ptr >= '0' && **ptr <= '9')
	{
		nbr = nbr * 10 + **ptr - '0';
		(*ptr)++;
	}
	return (nbr);
}

static double	get_frac_part(char **ptr)
{
	double	nbr;
	double	dividend;

	nbr = 0.0;
	dividend = 10.0;
	while (**ptr >= '0' && **ptr <= '9')
	{
		nbr += (**ptr - '0') / dividend;
		dividend *= 10;
		(*ptr)++;
	}
	return (nbr);
}

double	ft_atof_mv_ptr(char **ptr)
{
	int		sign;
	double	int_part;
	double	frac_part;

	while (ft_isspace(**ptr))
		(*ptr)++;
	sign = 1;
	if (**ptr == '+' || **ptr == '-')
	{
		if (**ptr == '-')
			sign = -1;
		(*ptr)++;
	}
	int_part = get_int_part(ptr);
	if (**ptr != '.')
		return (sign * int_part);
	(*ptr)++;
	frac_part = get_frac_part(ptr);
	return (sign * (int_part + frac_part));
}
