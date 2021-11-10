/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/10 19:52:01 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


void	check_entry(argc)
{
	if (argc != 5)
		printf("Error. Please include infile comand1 comand2 outfile");
	return ;
}

void	check_fd(int fd, char *file)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no file existing", 2);
		ft_putendl_fd(file, 2);
		exit(0);	
	}
}

void 	start_child(int fd, char **argv)
{
	int		fd_infile;
	
	close(fd[FD_READ_END]);   /* cerrar extremo no necesario */
	fd_infile = open(argv[1], O_RDONLY);
	check_fd(fd_infile, argv[1]);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fd[FD_WRITE_END], STDOUT_FILENO);
	close(fd[FD_WRITE_END]);
	
	
}

int main(int argc, char* argv[])   
{
    int		fd[2];
	int 	fd2;
    int		status;
	pid_t	pid;

	check_entry(argc);
	pipe(fd);				/* comunica los dos comandos */
	pid = fork();
	if (pid == -1)
		perror("Error. Proceso hijo no creado. \n");
	if(pid == 0)	/* hijo 1, ejecuta "comando1 */
		start_child(fd, argv);
	else					/* padre */
	{
		close(fd[FD_WRITE_END]);		/* extremo no necesario ya */
		pid = fork();
		if(pid == 0)			/* hijo 2, ejecuta "comando2" */
		{
			fd2 = open(FILE_NAME, O_WRONLY);  // abro fd del archivo txt donde escribe... cambiar
			dup2(fd[FD_READ_END], STDIN_FILENO);
			close(fd[FD_READ_END]);
			dup2(fd2, STDOUT_FILENO);
			execlp("/usr/bin/wc","wc",NULL);
		}
		else /* padre */
		{
			close(fd[FD_READ_END]);      /* cerrar extremo no necesario */
		}
	}
	/* wait para cada hijo */
	wait(&status);
	wait(&status);
    return 0;
}
