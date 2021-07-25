/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:42:32 by rcammaro          #+#    #+#             */
/*   Updated: 2021/03/18 17:15:02 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ADD_ONS_H
# define ADD_ONS_H

# include "libft.h"

int		ft_atoi_mv_ptr(char **ptr);
double	ft_atof(char *ptr);
double	ft_atof_mv_ptr(char **ptr);
void	*ft_free_split(char **array);
int		ft_isspace(char c);
char	**ft_split_charset(char *str, char *charset);

#endif
