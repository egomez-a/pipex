/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerrors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:59:29 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 13:59:04 by egomez-a         ###   ########.fr       */
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
	{
		perror("Fork error. Child not created");
		exit (errno);
	}
}

void	check_commands(int *check)
{
	if (check[0] == 0 || check[1] == 0)
	{
		perror("Command does not execute");
		exit (errno);
	}
}

