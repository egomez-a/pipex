/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:59:29 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 10:17:58 by egomez-a         ###   ########.fr       */
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

void	check_pid(pid_t pid, t_pipex pipex)
{
	if (pid < 0)
	{
		perror("Fork error. Child not created");
		freepointers(pipex);
		exit (errno);
	}
}

void	check_commands(int *check, t_pipex pipex)
{
	if (check[0] == 0 || check[1] == 0)
	{
		perror("Command does not execute");
		freepointers(pipex);
		exit (errno);
	}
}

void	check_fdoutfile(int fd_outfile, t_pipex pipex)
{
	if (fd_outfile < 0)
	{
		perror("Error creating or opening outfile\n");
		freepointers(pipex);
		exit (errno);
	}
}
