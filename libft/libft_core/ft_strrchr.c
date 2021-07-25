/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 03:27:50 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/19 03:53:25 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*last_match;
	char	ch;

	ptr = (char *)s;
	ch = (char)c;
	last_match = 0;
	while (*ptr)
	{
		if (*ptr == ch)
			last_match = ptr;
		ptr++;
	}
	if (ch == '\0')
		return (ptr);
	else
		return (last_match);
}
