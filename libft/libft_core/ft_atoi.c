/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 00:05:24 by rcammaro          #+#    #+#             */
/*   Updated: 2021/04/07 13:06:32 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	else
		return (0);
}

static long int	safe_add(long int nbr, char c, int sign)
{
	if (nbr > LONG_MIN / 10 && nbr < LONG_MAX / 10)
		return (nbr * 10 + sign * (c - '0'));
	if (sign == 1 && nbr > LONG_MAX / 10)
		return (LONG_MAX);
	if (sign == 1 && nbr == LONG_MAX / 10 && (c - '0') > LONG_MAX % 10)
		return (LONG_MAX);
	if (sign == -1 && nbr < LONG_MIN / 10)
		return (LONG_MIN);
	if (sign == -1 && nbr == LONG_MIN / 10 && -(c - '0') < LONG_MIN % 10)
		return (LONG_MIN);
	return (nbr * 10 + sign * (c - '0'));
}

static long int	ft_strtol(const	char *nptr)
{
	int			sign;
	long int	nbr;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	nbr = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = safe_add(nbr, *nptr, sign);
		nptr++;
	}
	return (nbr);
}

int	ft_atoi(const char *str)
{
	return (ft_strtol(str));
}
