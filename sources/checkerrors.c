/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:59:29 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 18:07:01 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_entry(argc)
{
	if (argc != 5)
	{
		perror("Error. Please include infile comand1 comand2 outfile\n");
		exit (errno);
	}
	return ;
}

void	check_fd(int fd, char *filename)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no file existing \n", 2);
		ft_putendl_fd(filename, 2);
		exit(1);	
	}
	else if (fd == -2)
	{
		ft_putstr_fd("pipex: can't access file\n", 2);
		ft_putendl_fd(filename, 2);
		exit(1);	
	}
}