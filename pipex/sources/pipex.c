/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 15:12:15 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freepointers(t_pipex pipex)
{
	if (pipex.cmd1)
		freematrix(pipex.cmd1);
	if (pipex.cmd2)
		freematrix(pipex.cmd2);
	if (pipex.path)
		freematrix(pipex.path);
}

void	start_child_1(int *fd, char **argv, t_pipex pipex, char **envp)
{	
	pipex.fd_in = open_infile(argv[1], pipex);
	close(fd[FD_READ_END]);
	dup2(pipex.fd_in, STDIN_FILENO);
	close(pipex.fd_in);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	if (execve(pipex.cmd1[0], pipex.cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		exit (errno);
	}
}

void	start_child_2(int *fd, pid_t pid, t_pipex pipex, char **envp)
{
	close(fd[FD_WRITE_END]);
	pid = fork();
	check_pid(pid);
	if (pid == 0)
	{
		dup2(fd[FD_READ_END], STDIN_FILENO);
		close(fd[FD_READ_END]);
		dup2(pipex.fd_out, STDOUT_FILENO);
		if (execve(pipex.cmd2[0], pipex.cmd2, envp) == -1)
		{
			perror("Could not execve cmd 2");
			exit (errno);
		}
	}
	else
		close(fd[FD_READ_END]);
}

int	main(int argc, char **argv, char **envp)
{
	int			fd[2];
	pid_t		pid;
	t_pipex		pipex;
	int			status;
	int			*check;

	check_entry(argc);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = env_variable(envp);
	check = check_cmd_path(pipex);
	pipe(fd);
	check_pipe(fd);
	pid = fork();
	if (pid == 0)
		start_child_1(fd, argv, pipex, envp);
	else if (pid > 0)
	{
		pipex.fd_out = open_outfile(argv[4]);
		start_child_2(fd, pid, pipex, envp);
	}
	wait(&status);
	wait(&status);
	freepointers(pipex);
	free(check);
	//atexit(leaks);
	return (0);
}
