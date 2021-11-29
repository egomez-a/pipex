/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:55:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 12:25:45 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	add_slash(char **paths)
{
	int		i;
	char	*aux;

	i = 0;
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = aux;
		i++;
	}
	paths[0] = ft_strtrim(paths[0], "PATH=");
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
		i = 0;
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			i++;
		}
		paths[0] = ft_strtrim(paths[0], "PATH=");
	}
	else
	{
		paths = NULL;
		printf("Error - no env variable found\n");
	}
	return (paths);
}
