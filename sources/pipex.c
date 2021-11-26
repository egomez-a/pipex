/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/26 12:29:52 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	start_child_1(int *fd, char **argv, t_pipex *pipex, char **envp)
{	
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	check_fd(fd_infile, argv[1]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	if (execve(*pipex->path, pipex->cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		free(pipex);
		exit(0);
	}
}

void	start_child_2(int *fd, char **argv, t_pipex *pipex, char **envp)
{
	int		fd_outfile;
	
	close(fd[FD_WRITE_END]);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(fd[FD_READ_END], STDIN_FILENO);
	close(fd[FD_READ_END]);
	dup2(fd_outfile, STDOUT_FILENO);
	if (execve(*pipex->path, pipex->cmd2, envp) == -1)
	{
    	perror("Could not execve cmd 2");
		free(pipex);
		exit(0);
	}
}

int main(int argc, char **argv, char **envp)
{
    int			fd[2];
	pid_t		pid;
	t_pipex		pipex;
	
	check_entry(argc);
	pipex.cmd1 = ft_split(argv[1], ' ');
	pipex.cmd2 = ft_split(argv[2], ' ');
	pipex.path = env_variable(envp);
	check_program(pipex);
	pipe(fd);
	if (pipe(fd) < 0)
		perror("Pipe error. Pipe not created. \n");
	pid = fork();
	if (pid == -1)
		perror("Fork error. Child not created. \n");
	if(pid == 0)
		start_child_1(fd, argv, &pipex, envp);
	else
	{
		close(fd[FD_WRITE_END]);
		pid = fork();
		if (pid == -1)
			perror("Fork error. Child not created. \n");
		if(pid == 0)
			start_child_2(fd, argv, &pipex, envp);
		else
			close(fd[FD_READ_END]);
	}
	waitpid(pid, NULL, 0);
	return 0;
}
