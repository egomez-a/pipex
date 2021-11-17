/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:43:18 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/15 21:53:20 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct t_pipex
{
	int		fd_in;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
	char	**path;
}	t_pipex;

int		open_infile(char *argv);
int		open_outfile(char *argv);
void	show_error(const char *error);
void	check_argc(int argc);
void	manage_errors(int argc, char **argv, char **envp, t_pipex *args);
int		double_free(char **array);
void	check_acces(t_pipex *args, char **cmd, int *bool);
int		*check_cmd(t_pipex *args);
void	check_rights(char *cmd1, char *cmd2, t_pipex *args);
void	path_slash(char **path);
char	**get_path(char **envp);
void	child_process(int *fd, t_pipex *args, char **envp);
void	parent_process(int *fd, int pid, t_pipex *args, char **envp);

#endif
