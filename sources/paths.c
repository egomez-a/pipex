/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:55:36 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 17:23:20 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**add_slash(char **paths)
{
	int		i;
	char	**aux;
	char 	*first;

	i = 0;
	
	while (paths[i])
		i++;
	aux = ft_calloc(sizeof (char *), i);
	i = 0;
	while (paths[i])
	{
		if (i == 0)
		{	
			first = ft_strtrim(paths[i], "PATH=");
			aux[i] = ft_strjoin(first, "/");
		}
		else
			aux[i] = ft_strjoin(aux[i], "/");
		free(paths[i]);
		i++;
	}
	free(paths);
	return (aux);
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
		if (!path_line)
		{
			perror("Error - no pathline in env\n");
			exit (errno);
		}
		paths = ft_split(path_line, ':');
		paths = add_slash(paths);
	}
	else
	{
		perror("Error - no env variable found\n");
		exit (errno);
	}
	return (paths);
}
