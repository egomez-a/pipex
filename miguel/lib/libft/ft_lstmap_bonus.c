/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:50:09 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/08 16:42:41 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*new;
	t_list	*aux;

	if (lst)
	{
		new = ft_lstnew(f(lst->content));
		aux = new;
		while (lst->next)
		{
			lst = lst->next;
			new->next = ft_lstnew(f(lst->content));
			if (!(new->next))
			{
				del(new->next);
				free(new->next);
				return (NULL);
			}
			new = new->next;
		}
		return (aux);
	}
	return (NULL);
}
