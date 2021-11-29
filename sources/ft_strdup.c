/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:03:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 11:38:08 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*
** strdup allocates sufficient memory for a copy of the string s1, does the
** copy, and returns a pointer to it.  The pointer may subsequently be used as
** an argument to the function free(3). If insufficient memory is available,
** NULL is returned and errno is set to ENOMEM.
*/

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*ptr;

	len = 0;
	while (s1[len])
		len++;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ptr))
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
