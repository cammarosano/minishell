/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcammaro <rcammaro@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 22:10:27 by rcammaro          #+#    #+#             */
/*   Updated: 2020/11/24 01:42:23 by rcammaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*ptr;

	if (!f || !lst)
		return (NULL);
	new_list = ft_lstnew((*f)(lst->content));
	if (!new_list)
		return (NULL);
	lst = lst->next;
	ptr = new_list;
	while (lst)
	{
		ptr->next = ft_lstnew((*f)(lst->content));
		if (!ptr->next)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ptr = ptr->next;
		lst = lst->next;
	}
	return (new_list);
}
