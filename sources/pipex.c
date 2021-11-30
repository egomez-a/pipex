/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/30 10:19:15 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freepointers(t_pipex pipex)
{
	freematrix(pipex.cmd1);
	freematrix(pipex.cmd2);
	freematrix(pipex.path);
}

void	start_child_1(int *fd, char **argv, t_pipex pipex, char **envp)
{	
	int		fd_infile;

	//printf("Entrando en el child 1\n");
	fd_infile = open(argv[1], O_RDONLY);
	// printf("Abierto el infile con fd = %d\n", fd_infile);
	check_fd(fd_infile, argv[1]);
	close(fd[FD_READ_END]);
	dup2(fd_infile, STDIN_FILENO);
	// printf("El STDIN_FILENO es %d\n", STDIN_FILENO);
	close(fd_infile);
	// printf("Saliendo del proceso hijo1\n");
	if (execve(pipex.cmd1[0], pipex.cmd1, envp) == -1)
	{
		perror("Could not execve cmd 1");
		freepointers(pipex);
		exit (errno);
	}
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
}

void	start_child_2(int *fd, char **argv, t_pipex pipex, char **envp)
{
	int		fd_outfile;

	// printf("Entrando en el child 2\n");
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// printf("Creado el outfile con fd = %d\n", fd_outfile);
	dup2(fd[FD_READ_END], STDIN_FILENO);
	close(fd[FD_READ_END]);
	if (execve(pipex.cmd2[0], pipex.cmd2, envp) == -1)
	{
		perror("Could not execve cmd 2");
		freepointers(pipex);
		exit (errno);
	}
	check_fdoutfile(fd_outfile, pipex);
	dup2(fd_outfile, STDOUT_FILENO);
	// printf("Saliendo del proceso hijo2\n");
}

void	child_2_process(int *fd, int pid, t_pipex pipex, char **argv, char **envp)
{
	printf("****Voy a generar el segundo proceso\n");
	pid = fork();
	printf("    el número pid del proceso Hijo2 generado es %d\n", pid);
	check_pid(pid, pipex);
	if (pid == 0)
		start_child_2(fd, argv, pipex, envp);
	else
	{
		close(fd[FD_READ_END]);
		close(fd[FD_WRITE_END]);
	}
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
	check_commands(check, pipex);
	pipe(fd);
	if (pipe(fd) < 0)
	{
		perror("Pipe error. Pipe not created");
		exit (errno);
	}
	pid = fork();
	printf("****He generado el primer proceso\n");
	printf("    el número pid del proceso Hijo1 generado es %d\n", pid);
	check_pid(pid, pipex);
	if (pid == 0)
		start_child_1(fd, argv, pipex, envp);
	child_2_process(fd, pid, pipex, argv, envp);
	wait(&status);
	wait(&status);
	freepointers(pipex);
	//atexit(leaks);
	return (0);
}
