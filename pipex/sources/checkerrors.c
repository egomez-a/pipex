/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:59:29 by egomez-a          #+#    #+#             */
/*   Updated: 2021/12/02 13:07:01 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_entry(int argc)
{
	if (argc != 5)
	{
		perror("Error. Please include infile comand1 comand2 outfile\n");
		exit (1);
	}
}

void	check_pid(pid_t pid)
{
	if (pid < 0)
		put_error("Fork error. Child not created");
}

void	check_commands(int *check)
{
	if (check[0] == 0 || check[1] == 0)
	{
		perror("command not found");
		exit(2);
	}
}

void	check_pipe(int *fd)
{
	if (pipe(fd) < 0)
		put_error("Pipe error. Pipe not created");
}

void	put_error(const char *error)
{
	perror(error);
	exit (errno);
}
