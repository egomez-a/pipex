/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:42:20 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/17 15:47:15 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


void	check_entry(argc)
{
	if (argc != 5)
	{
		printf("Error. Please include infile comand1 comand2 outfile\n");
	}
	return ;
}

void	check_fd(int fd, char *filename)
{
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no file existing ", 2);
		ft_putendl_fd(filename, 2);
		exit(0);	
	}
	else if (fd == -2)
	{
		ft_putstr_fd("pipex: can't access file", 2);
		ft_putendl_fd(filename, 2);
		exit(0);	
	}
}

void 	start_child(int *fd, char **argv)
{
	int		fd_infile;
	
	close(fd[FD_READ_END]);   				/* cerrar extremo no necesario */
	fd_infile = open(argv[1], O_RDONLY);	/* abro in file */
	printf("El fd_infile es %d", fd_infile);
	printf("El STDIN_FILENO es %d,", STDIN_FILENO);
	check_fd(fd_infile, argv[1]);			/* compruebo que puedo abrir */
	dup2(fd_infile, STDIN_FILENO);			/* duplico para que sea STDIN */
	
	close(fd_infile); 						/* lo cierro */
//	dup2(fd[FD_WRITE_END], STDOUT_FILENO);	/* duplico para pipe */
//	close(fd[FD_WRITE_END]);				/* cierro el fd del pipe */
}

void	env_variable(char **envp)
{
	int		i;
	char	*path_line;
	char	**paths;

	i = 0;
	if (envp)
	{
		while(envp[i])
		{
			paths = ft_strnstr(env[i], "PATH=", ft_strlen("PATH="));
			if (paths != NULL)
				break;
			i++;
		}
		paths = ft_split(path_line, ':');
		
	}
	else 
		printf("Error - no env variable provided\n");
}

int main(int argc, char **argv, char **envp)
{
    int		fd[2];
	int		status;
	pid_t	pid;
	t_pipex	pipe;

// Busca que tengo la variable de entorno 
// Busca que existe path
// Separa con splits los distintos paths 
// Añade un / 
// comprueba que el nombre del command existe 

	check_entry(argc);
	pipe.fd_in = open_infile(argv[1]);
	env_variable(envp);
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
	//		execlp("/usr/bin/wc","wc",NULL);
	 	}
	 	else /* padre */
	 	{
	 		close(fd[FD_READ_END]);      /* cerrar extremo no necesario */
	 	}
	}
	/* wait para cada hijo */
	// wait(&status);
	// wait(&status);
    return 0;
}
