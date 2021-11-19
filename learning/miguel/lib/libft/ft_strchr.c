/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:27:35 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/08 16:46:05 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		*aux;

	i = 0;
	aux = (char *)s;
	while (aux[i])
	{
		if (aux[i] == c)
			return (&aux[i]);
		i++;
	}
	if (aux[i] == '\0' && c == '\0')
		return (&aux[i]);
	return (NULL);
}
