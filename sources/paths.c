/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:55:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/26 12:32:50 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	check_program(t_pipex pipex)
{
	int		i;
	char	*cmd[2];

	i = 0;
	while (pipex.path[i])
	{
		cmd[0] = ft_strjoin(pipex.path[i], pipex.cmd1[0]);
		if (!access(cmd[0], X_OK))
			pipex.cmd1[0] = ft_strdup(cmd[1]);
		cmd[1] = ft_strjoin(pipex.path[i], pipex.cmd2[0]);
		if (!access(cmd[1], X_OK))
			pipex.cmd2[0] = ft_strdup(cmd[1]);
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

char	**env_variable(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
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
	{
		paths = NULL;
		printf("Error - no env variable found\n");
	}
	return (paths);
}
