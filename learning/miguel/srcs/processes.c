/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mangarci <mangarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:32:36 by mangarci          #+#    #+#             */
/*   Updated: 2021/11/15 22:06:54 by mangarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_process(int *fd, t_pipex *args, char **envp)
{
	close(fd[READ_END]);
	if (dup2(args->fd_in, STDIN_FILENO) < 0)
		show_error("Error");
	close(args->fd_in);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		show_error("Error");
	close(fd[WRITE_END]);
	if (execve(args->cmd1[0], args->cmd1, envp) < 0)
		show_error("Execution failed");
}

void	parent_process(int *fd, int pid, t_pipex *args, char **envp)
{
	close(fd[WRITE_END]);
	pid = fork();
	if (!pid)
	{
		close(fd[WRITE_END]);
		if (dup2(fd[READ_END], STDIN_FILENO) < 0)
			show_error("Error");
		close(fd[READ_END]);
		if (dup2(args->fd_out, STDOUT_FILENO) < 0)
			show_error("Error");
		close(args->fd_out);
		if (execve(args->cmd2[0], args->cmd2, envp) < 0)
			show_error("Execution failed");
	}
	else if (pid > 0)
	{
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	else
		show_error("Error: child2 process failed");
}
