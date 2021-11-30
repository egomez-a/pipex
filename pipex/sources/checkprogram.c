/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkprogram.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 18:47:37 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 19:54:37 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_program(t_pipex pipex, char **cmd, int *check)
{
	if (access(cmd[0], X_OK) == 0 && check[0] == 0)
	{
		free(pipex.cmd1[0]);
		pipex.cmd1[0] = ft_strdup(cmd[0]);
		check[0] = 1;
		free(cmd[0]);
	}
	else
		free(cmd[0]);
	if (access(cmd[1], X_OK) == 0 && check[1] == 0)
	{
		free(pipex.cmd2[0]);
		pipex.cmd2[0] = ft_strdup(cmd[1]);
		check[1] = 1;
		free(cmd[1]);
	}
	else
		free(cmd[1]);
}

void	check_cmd_pathcmd1(t_pipex pipex, char **cmd, int i)
{
	if (pipex.cmd1[0][0] == '/')
		cmd[0] = ft_strdup(pipex.cmd1[0]);
	else
		cmd[0] = ft_strjoin(pipex.path[i], pipex.cmd1[0]);
}

void	check_cmd_pathcmd2(t_pipex pipex, char **cmd, int i)
{
	if (pipex.cmd2[0][0] == '/')
		cmd[1] = ft_strdup(pipex.cmd2[0]);
	else
		cmd[1] = ft_strjoin(pipex.path[i], pipex.cmd2[0]);
}

void	*check_cmd_path(t_pipex pipex)
{
	int		i;
	char	*cmd[2];
	int		*check;

	i = 0;
	check = (int *)calloc(2, sizeof(int));
	while (pipex.path[i])
	{
		cmd[0] = NULL;
		cmd[1] = NULL;
		if (check[0] == 0)
			check_cmd_pathcmd1(pipex, cmd, i);
		if (check[1] == 0)
			check_cmd_pathcmd2(pipex, cmd, i);
		check_program(pipex, cmd, check);
		i++;
	}
	check_commands(check);
	free(check);
	return (0);
}
