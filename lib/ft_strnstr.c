/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 15:38:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/17 15:40:24 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
** The strnstr() function locates the first occurrence of the null-terminated
** string needle in the string haystack, where not more than len characters are
** searched.  Characters that appear after a `\0' character are not searched.
** Return Values: If needle is an empty string, haystack is returned; if needle
** occurs nowhere in haystack, NULL is returned; otherwise a pointer to the
** first character of the first occurrence of needle is returned.
*/

char	*ft_strnstr(const char *hst, const char *ndl, size_t len)
{
	unsigned int		i;
	unsigned int		j;

	if (ndl[0] == '\0')
		return ((char *)hst);
	i = 0;
	while (hst[i] && i < len)
	{
		j = 0;
		if (hst[i] == ndl[j])
		{
			while (i + j < len && hst[i + j] == ndl[j])
			{
				j++;
				if (!ndl[j])
					return ((char *)&hst[i]);
			}
		}
		i++;
	}
	return (0);
}
