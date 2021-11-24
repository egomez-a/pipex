/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:55:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/24 20:53:11 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_program(char *argv1, char *argv2, t_pipe pipe)
{
	int		i;
	char	*cmd[2];

	pipe->cmd1 = ft_split(argv1, ' ');
	pipe->cmd2 = ft_split(argv2, ' ');
	i = 0;
	while (pipe->paths[i])
	{
		cmd[0] = ft_strjoin(pipe->path[i], pipe->cmd1[0]);
		if (!access(cmd[0], X_OK))
			pipe->cmd1[0] = ft_strdup(cmd[1]);
		cmd[1] = ft_strjoin(pipe->path[i], pipe->cmd2[0]);
		if (!access(cmd[1], X_OK))
			pipe->cmd2[0] = ft_strdup(cmd[1]);
	}
}

void	add_slash(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	paths[0] = ft_strtrim(paths[0], "PATH=");
	i = 0;
	while (paths[i])
	{
		printf("El path %d es %s\n", i, paths[i]);
		i++;
	}
}

void	env_variable(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
	paths = NULL;
	if (envp)
	{
		while (envp[i])
		{
			path_line = ft_strnstr(envp[i], "PATH=", ft_strlen("PATH="));
			if (path_line != NULL)
				break ;
			i++;
		}
		paths = ft_split(path_line, ':');
		add_slash(paths);
	}
	else
		printf("Error - no env variable found\n");
}
