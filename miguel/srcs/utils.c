/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:14:30 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/16 14:27:02 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	path_slash(char **path)
{
	int		i;
	char	*aux;

	i = 0;
	while (path[i])
	{
		aux = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = aux;
		i++;
	}
}

char	**get_path(char **envp)
{
	int		i;
	char	*aux;
	char	**path;

	i = 0;
	while (envp[i])
	{
		aux = ft_strnstr(envp[i], "PATH", ft_strlen("PATH"));
		if (aux)
		{
			aux++;
			path = ft_split(aux, ':');
			path_slash(path);
			return (path);
		}
		i++;
	}
	return (NULL);
}
