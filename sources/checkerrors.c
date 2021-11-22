/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:59:29 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/22 10:48:09 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_entry(argc)
{
	if (argc != 5)
	{
		printf("Error. Please include infile comand1 comand2 outfile\n");
	}
	return ;
}

void	check_fd(int fd, char *filename)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no file existing ", 2);
		ft_putendl_fd(filename, 2);
		exit(1);	
	}
	else if (fd == -2)
	{
		ft_putstr_fd("pipex: can't access file", 2);
		ft_putendl_fd(filename, 2);
		exit(1);	
	}
}