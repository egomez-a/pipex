/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:37:16 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 15:10:09 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *argv, t_pipex pipex)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		perror ("No infile existing");
		freepointers(pipex);
		exit (errno);
	}
	else if (fd == -2)
	{
		perror ("Can't access file");
		freepointers(pipex);
		exit (errno);
	}
	return (fd);
}

int	open_outfile(char *argv)
{
	int	fd;

	fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror ("Error creating or opening outfile\n");
		exit (errno);
	}
	return (fd);
}
