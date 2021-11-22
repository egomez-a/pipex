/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/22 11:11:58 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void 	start_child(int *fd, t_pipe *pipe, char **envp)
{	
	close(fd[FD_READ_END]);   				/* cerrar extremo no necesario */
	dup2(pipe.fd_in, STDIN_FILENO);			/* duplico para que sea STDIN */
	close(pipe.fd_in); 						/* lo cierro */
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);	/* duplico para pipe */
	close(fd[FD_WRITE_END]);				/* cierro el fd del pipe */
	if (execve(pipe->cmd1[0], pipe.cmd1, envp) == -1)
    	perror("Could not execve");
}

int	open_infile(char *argv1)
{
	int fd;

	fd = open(argv1, O_RDONLY);
	check_fd(fd, argv1);
	return (fd);
}

int main(int argc, char **argv, char **envp)
{
    int			fd[2];
	int			fd2;
	int			status;
	pid_t		pid;
	t_pipe		pipe;

	check_entry(argc);
	pipe.fd_in = open_infile(argv[1]);
	env_variable(envp);
	check_program(argv[2], argv[3], pipe);
	pipe(fd);				/* comunica los dos comandos */
	if (pipe(fd < 0))
		perror("Pipe error. Pipe not created. \n");
	pid = fork();
	if (pid == -1)
		perror("Fork error. Child not created. \n");
	if(pid == 0)	/* hijo 1, ejecuta "comando1 */
		start_child(fd, &pipe, envp);
	// else					/* padre */
	// {
	// 	close(fd[FD_WRITE_END]);		/* extremo no necesario ya */
	// 	pid = fork();
	//  	if(pid == 0)			/* hijo 2, ejecuta "comando2" */
	//  	{
	//  		fd2 = open(argv[1], O_WRONLY);  // abro fd del archivo txt donde escribe... cambiar
	//  		dup2(fd[FD_READ_END], STDIN_FILENO);
	//  		close(fd[FD_READ_END]);
	//  		dup2(fd2, STDOUT_FILENO);
	// //		execlp("/usr/bin/wc","wc",NULL);
	//  	}
	//  	else /* padre */
	//  	{
	//  		close(fd[FD_READ_END]);      /* cerrar extremo no necesario */
	//  	}
	// }
	/* wait para cada hijo */
	// wait(&status);
	// wait(&status);
    return 0;
}
