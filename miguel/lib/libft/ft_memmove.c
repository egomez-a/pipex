/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:00:48 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/08 16:44:15 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dst;
	if ((dst == '\0' && src == '\0') || len <= 0)
		return (dst);
	if (str1 < str2)
	{
		str1 = str1 + (len - 1);
		str2 = str2 + (len - 1);
		while (len-- > 0)
			*str2-- = *str1--;
		return (dst);
	}
	while (len-- > 0)
		*str2++ = *str1++;
	return (dst);
}
