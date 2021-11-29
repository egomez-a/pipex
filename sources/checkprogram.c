/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkprogram.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:47:37 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 09:43:56 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_program(t_pipex pipex, char **cmd, int *check)
{
	if (access(cmd[0], X_OK) == 0)
	{
		printf("La cadena cmd[0] es %s\n", cmd[0]);
		free(pipex.cmd1[0]);
		pipex.cmd1[0] = ft_strdup(cmd[0]);
		check[0] = 1;
	}
	if (access(cmd[1], X_OK) == 0)
	{
		printf("La cadena cmd[1] es %s\n", cmd[0]);
		free(pipex.cmd2[0]);
		pipex.cmd2[0] = ft_strdup(cmd[1]);
		check[1] = 1;
	}
}

int	*check_cmd_path(t_pipex pipex)
{
	int		i;
	char	*cmd[2];
	int		*check;

	i = 0;
	check = (int *)calloc(2, sizeof(int));
	while (pipex.path[i])
	{
		if (pipex.cmd1[0][0] == '/')
			cmd[0] = ft_strdup(pipex.cmd1[0]);
		else
			cmd[0] = ft_strjoin(pipex.path[i], pipex.cmd1[0]);
		if (pipex.cmd2[0][0] == '/')
			cmd[1] = ft_strdup(pipex.cmd2[0]);
		else
			cmd[1] = ft_strjoin(pipex.path[i], pipex.cmd2[0]);
		check_program(pipex, cmd, check);
		if (check[0] == 1)
			break;
		i++;
	}
	return (check);
}
