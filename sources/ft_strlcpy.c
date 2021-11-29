/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:17:27 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 16:16:30 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*
** strlcpy() takes the full size of the destination buffer and guarantees
** NUL-termination if there is room.  Room for the NUL should be included in
** dstsize. Returns size of src, the string it tried to create.
** strlcpy() copies up to dstsize - 1 characters from the string src to dst,
** NUL-terminating the result if dstsize is not 0.
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	lensrc;

	if (!src || !dest)
		return (0);
	lensrc = 0;
	while (src[lensrc])
		lensrc++;
	j = 0;
	if (size > 0)
	{
		while (src[j] != '\0' && j < size - 1)
		{
			dest[j] = src[j];
			j++;
		}
		if (j < size)
			dest[j] = '\0';
	}
	return (lensrc);
}
