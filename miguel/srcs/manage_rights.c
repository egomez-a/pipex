/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 20:00:55 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/16 14:20:28 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	check_acces(t_pipex *args, char **cmd, int *bool)
{
	if (!access(cmd[0], X_OK))
	{
		free(args->cmd1[0]);
		args->cmd1[0] = ft_strdup(cmd[0]);
		bool[0] = 1;
	}
	free(cmd[0]);
	if (!access(cmd[1], X_OK))
	{
		free(args->cmd2[0]);
		args->cmd2[0] = ft_strdup(cmd[1]);
		bool[1] = 1;
	}
}

int	*check_cmd(t_pipex *args)
{
	int		i;
	int		*bool;
	char	*cmd[2];

	bool = (int *)calloc(2, sizeof(int));
	i = 0;
	while (args->path[i])
	{
		if (args->cmd1[0][0] == '/')
			cmd[0] = ft_strdup(args->cmd1[0]);
		else
			cmd[0] = ft_strjoin(args->path[i], args->cmd1[0]);
		if (args->cmd2[0][0] == '/')
			cmd[1] = ft_strdup(args->cmd2[0]);
		else
			cmd[1] = ft_strjoin(args->path[i], args->cmd2[0]);
		check_acces(args, cmd, bool);
		free(cmd[1]);
		i++;
	}
	return (bool);
}

void	check_rights(char *cmd1, char *cmd2, t_pipex *args)
{
	int	*bool;

	args->cmd1 = ft_split(cmd1, ' ');
	args->cmd2 = ft_split(cmd2, ' ');
	bool = check_cmd(args);
	if (!bool[0] || !bool[1])
		show_error("Error: problem with CMD");
	ft_dfree(args->path);
	free(bool);
}
