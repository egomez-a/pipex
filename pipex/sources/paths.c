/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:55:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/12/02 13:07:17 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_lenght(t_pipex *pipex)
{
	int		i;

	i = 0;
	while (pipex->path[i])
		i++;
	return (i);
}

char	**add_slash(char **paths)
{
	int		i;
	char	**aux;
	char	*first;

	i = 0;
	while (paths[i])
		i++;
	aux = ft_calloc(sizeof (char *), i + 1);
	i = 0;
	while (paths[i])
	{
		if (i == 0)
		{	
			first = ft_strtrim(paths[i], "PATH=");
			aux[i] = ft_strjoin(first, "/");
			free(first);
		}
		else
			aux[i] = ft_strjoin(paths[i], "/");
		free(paths[i]);
		i++;
	}
	aux[i] = NULL;
	free(paths);
	return (aux);
}

void	check_error_path(char *path_line)
{
	if (!path_line)
	{
		perror ("Error - no pathline in env\n");
		exit (errno);
	}
}

char	**env_variable(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;
	char	**p;

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
		check_error_path(path_line);
		p = ft_split(path_line, ':');
		paths = add_slash(p);
	}
	else
	{
		perror ("Error - no env variable found\n");
		exit (errno);
	}
	return (paths);
}
