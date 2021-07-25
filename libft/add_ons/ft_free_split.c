/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:48:02 by rcammaro          #+#    #+#             */
/*   Updated: 2021/07/24 01:38:07 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "add_ons.h"

void	*ft_free_split(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}
