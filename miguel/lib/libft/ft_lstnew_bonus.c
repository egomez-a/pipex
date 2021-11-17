/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 16:31:30 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/08 16:41:56 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list));
	if (!(new))
		return (NULL);
	new->content = (void *) content;
	new->next = NULL;
	return (new);
}
