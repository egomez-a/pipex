/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:35:57 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 16:16:30 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* Escribe la cadena de caracteres ’s’ sobre el descriptor de fichero 
** proporcionado, seguida de un salto de línea.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		ft_putchar_fd('\n', fd);
	}
}
