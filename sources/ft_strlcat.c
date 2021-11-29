/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:47:51 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 16:16:30 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/*
** strlcat() takes the full size of the destination buffer and guarantees
** NUL-termination if there is room.  Room for the NUL should be included in
** dstsize. Returns size of src, the string it tried to create.
** strlcat() appends string src to the end of dst.  It will append at most
** dstsize -strlen(dst) - 1 characters.  It will then NUL-terminate, unless
** dstsize is 0 or the original dst string was longer than dstsize (in practice
** this should not happen as it means that either dstsize is incorrect or that
** dst is not a proper string). The function returns the lenght of the string
** it is trying to create: lenght of src plus initial lenght of dst
*/

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendst;
	size_t	i;

	lensrc = 0;
	lendst = 0;
	while (src[lensrc])
		lensrc++;
	if (size == 0)
		return (lensrc);
	while (lendst < size && dest[lendst])
		lendst++;
	if (size <= lendst)
		return (size + lensrc);
	i = 0;
	while ((src[i]) && ((lendst + i + 1) < size))
	{
		dest[i + lendst] = src[i];
		i++;
	}
	if (lendst != size)
		dest[lendst + i] = '\0';
	return (lendst + lensrc);
}
