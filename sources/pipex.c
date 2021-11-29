/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 09:39:01 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	start_child_1(int *fd, char **argv, t_pipex *pipex, char **envp)
{	
	int		fd_infile;

	printf("Entrando en el child 1");
	fd_infile = open(argv[1], O_RDONLY);
	printf("Abierto el infile con fd = %d", fd_infile);
	check_fd(fd_infile, argv[1]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	if (execve(pipex->cmd1[0], pipex->cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		free(pipex);
		exit(0);
	}
}

void	start_child_2(int *fd, char **argv, t_pipex *pipex, char **envp)
{
	int		fd_outfile;
	
	printf("Entrando en el child 2");
	close(fd[FD_WRITE_END]);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(fd[FD_READ_END], STDIN_FILENO);
	close(fd[FD_READ_END]);
	dup2(fd_outfile, STDOUT_FILENO);
	if (execve(pipex->cmd2[0], pipex->cmd2, envp) == -1)
	{
    	perror("Could not execve cmd 2");
		free(pipex);
		exit(0);
	}
}

int main(int argc, char **argv, char **envp)
{
    int			fd[2];
	int 		i;
	pid_t		pid;
	t_pipex		pipex;
	int 		*check;
	
	check_entry(argc);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = env_variable(envp);
	printf("Command 1 es %s %s %s\n", pipex.cmd1[0], pipex.cmd1[1], pipex.cmd1[2]);
	printf("Command 1 es %s %s\n", pipex.cmd2[0], pipex.cmd2[1]);
	i = 0;
	while (pipex.path[i])
	{
		printf("Paths %s %s %s %s %s %s\n", pipex.path[0], pipex.path[1], pipex.path[2], pipex.path[3], pipex.path[4], pipex.path[5]);
		i++;
	}
	check = check_cmd_path(pipex);
	if (check[0] == 0 || check[1] == 0)
		printf("Error: not able to execute cmd");
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
