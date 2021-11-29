/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 15:58:19 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	freepointers(t_pipex pipex)
{
	freematrix(pipex.cmd1);
	freematrix(pipex.cmd2);
	freematrix(pipex.path);
}

void	start_child_1(int *fd, char **argv, t_pipex pipex, char **envp)
{	
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	check_fd(fd_infile, argv[1]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	if (execve(pipex.cmd1[0], pipex.cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		freepointers(pipex);
		exit (errno);
	}
}

void	start_child_2(int *fd, char **argv, t_pipex pipex, char **envp)
{
	int		fd_outfile;
	
	close(fd[FD_WRITE_END]);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile < 0)
	{
		perror("Error creating or opening outfile\n");
		exit (errno);
	}
	dup2(fd[FD_READ_END], STDIN_FILENO);
	close(fd[FD_READ_END]);
	dup2(fd_outfile, STDOUT_FILENO);
	if (execve(pipex.cmd2[0], pipex.cmd2, envp) == -1)
	{
    	perror("Could not execve cmd 2");
		freepointers(pipex);
		exit (errno);
	}
}

void	child_2_process(int *fd, int pid, t_pipex pipex, char **argv, char **envp)
{
	close(fd[FD_WRITE_END]);
	pid = fork();
	if (pid < 0)
	{
		perror("Fork error. Child not created. \n");
		exit (errno);
	}
	if(pid == 0)
		start_child_2(fd, argv, pipex, envp);
	else
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
	}
}

int main(int argc, char **argv, char **envp)
{
    int			fd[2];
	pid_t		pid;
	t_pipex		pipex;
	int 		status;
	int 		*check;
	
	check_entry(argc);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = env_variable(envp);
	check = check_cmd_path(pipex);
	if (check[0] == 0 || check[1] == 0)
	{
		perror("Command does not execute");
		exit (errno);
	}
	pipe(fd);
	if (pipe(fd) < 0)
	{
		perror("Pipe error. Pipe not created");
		exit (errno);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Fork error. Child not created");
		exit (errno);
	}
	start_child_1(fd, argv, pipex, envp);
	child_2_process(fd, pid, pipex, argv, envp);
	wait(&status);
	wait(&status);
	freepointers(pipex);
	atexit(leaks);
	return 0;
}
