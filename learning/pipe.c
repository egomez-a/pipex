/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:13:34 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/10 15:44:51 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Funcion pipe: el pipe es un mecanismo de procesos relacionados (padre-hijo o 
// hijo-hijo) y unidireccional. Es una tuberia por la que fluyen datos en una dirección. 
// Va asociado a dos fd. Uno de escritura y otro de lectura

// Funciones:   
// crear pipe:  	int pipe (int fd[2]); *fd[0] : READ; fd[1]: WRITE 
// escribe: 		ssize_t write(int fd, const void *buf, size_t nr)  fd de escritura
// lee:				ssize_t read(int fd, void *buf, size_t nr)   fd de lectura
// cierra:			int close (int fd)   cualquier fd

// El primer paso es llamar a la funcion pipe. 
// El segundo paso es fork, que crea proceso hijo con dos fds también
// el tercero es ir cerrando los fds que no usemos del padre y del hijo
// En nuestro caso el hijo va a escribir y el padre a leer, por lo que cerraremos
// el fd del hijo de lectura y el fd de escritura del padre

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int 	fd[2];
	pid_t	pidC;
	char	buf[10];
	int 	num;  /* numero de bytes leidos */

	pipe(fd);    /* tarea pendiente: error management */
	pidC = fork();
	switch(pidC)
	{
		case 0:   /* si pidC es 0, el hijo es está procesando. */ 
			close(fd[0]);  /* cerramos el fd de lectura del hijo */ 
			write(fd[1], "hijow", 5);
			close(fd[1]);
			exit(0);
			break;
		case -1: /* si pidC es -1, error y el hijo no se ha creado. */ 
			break;
		default: /* si pidC es otro valor, el padre se está ejecutando y el pidC corresponderá al hijo. */ 
			close(fd[1]);  /* cerramos el fd de escritura del padre */ 
			num = read(fd[0], buf, sizeof(buf));   /* el tercer argumento es el numero máximo de bytes que vamos a leer */
			printf("Padre lee %d bytes: %s \n", num, buf);
			close(fd[0]);
			break;
	}
	return 0;
}
