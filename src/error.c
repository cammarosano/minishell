/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:34:15 by rcammaro          #+#    #+#             */
/*   Updated: 2021/06/02 18:34:16 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_perror(char *func_name)
{
	int	error_code;

	error_code = errno;
	if (func_name)
	{
		ft_putstr_fd(func_name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(error_code), 2);
}

// prints error message based on errno and returns "return_value"
int	ft_perror_ret(char *func_name, int return_value)
{
	ft_perror(func_name);
	return (return_value);
}
