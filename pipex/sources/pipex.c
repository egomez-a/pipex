/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/12/02 13:09:25 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pointers(t_pipex pipex)
{
	freematrix(pipex.path);
	freematrix(pipex.cmd1);
	freematrix(pipex.cmd2);
}

void	start_child_1(int *fd, char **argv, t_pipex pipex, char **envp)
{	
	pipex.fd_in = open_infile(argv[1]);
	close(fd[FD_READ_END]);
	if (dup2(pipex.fd_in, STDIN_FILENO) < 0)
		put_error("Dup Error");
	close(pipex.fd_in);
	if (dup2(fd[FD_WRITE_END], STDOUT_FILENO) < 0)
		put_error("Dup Error");
	close(fd[FD_WRITE_END]);
	execve(pipex.cmd1[0], pipex.cmd1, envp);
	perror("command not found");
	exit(127);
}

void	start_child_2(int *fd, pid_t pid, t_pipex pipex, char **envp)
{
	close(fd[FD_WRITE_END]);
	pid = fork();
	check_pid(pid);
	if (pid == 0)
	{
		close(fd[FD_WRITE_END]);
		if (dup2(fd[FD_READ_END], STDIN_FILENO) < 0)
			put_error("Dup Error");
		close(fd[FD_READ_END]);
		if (dup2(pipex.fd_out, STDOUT_FILENO) < 0)
			put_error("Dup Error");
		close(pipex.fd_out);
		execve(pipex.cmd2[0], pipex.cmd2, envp);
		perror("command not found");
		exit(127);
	}
	else
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex		pipex;
	int			fd[2];
	pid_t		pid;
	int			status;

	check_entry(argc);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = env_variable(envp);
	pipex.len = path_lenght(&pipex);
	check_cmd_path(&pipex);
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
	return (0);
}
