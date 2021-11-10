/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_eof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:44:08 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/10 18:06:02 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* vemos el caso de que leo de un pipe en el que está cerrado el extremo de escritura
** al tratar de leer, si hay datos dentro del pipe se leen
** en la siguiente verá un EOF (end of file) y la función read devuelve 0 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (void)
{
	int fd[2]; 			// file descriptors array
	char buf[100];		// buffer lectura
	int	num;			// num bytes leidos pipe

	pipe(fd);			// crea pipe. TODO: error handling

	switch(fork())		// crea nuevo proceso
	{
		case 0:			// hijo. El hijo va a escribir
			close(fd[0]);		// cierra extremo lectura
			write(fd[1], "abcde ...", 9);  // escribe en el pipe
			write(fd[1], "fghij ...", 9);  // escribe en el pipe
			sleep(5);						// espera 5 segundos
				// si dejo un bucle infinito con while(1){sleep(1)}, el hijo no se cierra y el padre no 
				//termina nunca. tendría que cargarme al hijo con kill -9 PID del hijo
			close(fd[1]);		// cierra extremo escritura
			exit(0);
			break;

		case -1:		// error
			break;
		
		default:		// padre
			close(fd[1]);		// cierra extremo escritura
			while(0 < (num = read(fd[0], buf, sizeof(buf)))) /* lee hasta que se vacia el pipe */
			{
				buf[num] = 0;
				printf("El padre recibe %d bytes, %s \n", num, buf);
			}
			printf("El padre va a terminar ya... \n");
			close(fd[0]);
			break;
	}
	return 0;
}