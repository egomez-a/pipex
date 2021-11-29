/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/29 15:30:36 by egomez-a         ###   ########.fr       */
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

	printf("Entrando en el child 1\n");
	fd_infile = open(argv[1], O_RDONLY);
	printf("Abierto el infile con fd = %d\n", fd_infile);
	check_fd(fd_infile, argv[1]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	printf("Saliendo del proceso hijo1\n");
	if (execve(pipex.cmd1[0], pipex.cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		freepointers(pipex);
		exit(0);
	}
}

void	start_child_2(int *fd, char **argv, t_pipex pipex, char **envp)
{
	int		fd_outfile;
	
	printf("Entrando en el child 2\n");
	close(fd[FD_WRITE_END]);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("Outfile creada con fd = %d\n", fd_outfile);
	if (fd_outfile < 0)
		printf("Error creating or opening outfile\n");
	dup2(fd[FD_READ_END], STDIN_FILENO);
	close(fd[FD_READ_END]);
	dup2(fd_outfile, STDOUT_FILENO);
	//printf("Saliendo del proceso hijo2\n");
	if (execve(pipex.cmd2[0], pipex.cmd2, envp) == -1)
	{
    	perror("Could not execve cmd 2\n");
		freepointers(pipex);
		exit(0);
	}
}

void	child_2_process(int *fd, int pid, t_pipex pipex, char **argv, char **envp)
{
	printf("****Voy a generar el segundo proceso\n");
	close(fd[FD_WRITE_END]);
	pid = fork();
	printf("    el número pid del proceso Hijo2 generado es %d\n", pid);
	if (pid == -1)
		perror("Fork error. Child not created. \n");
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
	int 		i;
	t_pipex		pipex;
	int 		status;
	int 		*check;
	
	check_entry(argc);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = env_variable(envp);
	// printf("Command 1 es %s %s\n", pipex.cmd1[0], pipex.cmd1[1]);
	// printf("Command 1 es %s %s\n", pipex.cmd2[0], pipex.cmd2[1]);
	i = 0;
	while (pipex.path[i])
	{
		printf("Paths %d %s\n", i, pipex.path[i]);
		i++;
	}
	check = check_cmd_path(pipex);
	if (check[0] == 0 || check[1] == 0)
	{
		perror("pipex - cmd does not execute");
		exit (errno);
	}
	pipe(fd);
	printf("Acabo de iniciar el pipe\n");
	printf("     El fd del pipe de lectura es %d\n", fd[FD_READ_END]);
	printf("     El fd del pipe de escritura es %d\n", fd[FD_WRITE_END]);
	if (pipe(fd) < 0)
		perror("     Pipe error. Pipe not created. \n");
	pid = fork();
	printf("****He generado el primer proceso\n");
	printf("    el número pid del proceso Hijo1 generado es %d\n", pid);
	if (pid < 0)
	{
		perror("Fork error. Child not created. \n");
		exit (errno);
	}
	//if(pid == 0)
	start_child_1(fd, argv, pipex, envp);
	child_2_process(fd, pid, pipex, argv, envp);
	wait(&status);
	wait(&status);
	freepointers(pipex);
//	atexit(leaks);
	return 0;
}
