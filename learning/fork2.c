/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:55:13 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/10 15:11:02 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// Este programa es para crear 5 hijos
// El bucle for es para que el padre vaya creando hijos
#define NUM_CHILD 5

/* Funcion que hará el hijo. Sirve por ejemplo para calcular un numero aleatorio. 
/* Semilla es srand, y el numero está entre 0 y 255 */
int	doSomething(void)
{
	int ret;
	
	srand(getpid());
	ret = (rand() % 256);
	printf("Hijo: PID = %d, valor aleatorio %d \n", getpid(), ret);

	return (ret);
}

int main(void)
{
	pid_t pidC;
	int	status;
	
	for(int i = 0; i < NUM_CHILD; i++)
	{
		pidC = fork();
		if (pidC > 0)
			continue;
			/*  continua haciendo hijos */
		else if (pidC == 0)
		{
			exit(doSomething());
			/* para que no haga hijos de hijos. doSomething devuelve un valor*/
		}
		else 
		{
			/*error*/
		}
	}
	for(int i = 0; i < NUM_CHILD; i++)
	{
		pidC = wait(&status);
		/* La funcion wait sera llamada por el proceso padre para esperar que un proceso hijo termine.   */
		/* Como argumento de entrada tiene que tener un puntero a una variable status. En esta variable */
		/* se almacenará información de estaod de este hijo que ha terminado, y dara como retorno un PID del */
		/* hijo que ha terminado */
		/* La variable se puede inspeccionar con la macro WEXITSTATUS   */
		printf("Padre de PID = %d, Hijo de PID = %d terminado, estado = %d\n", getpid(), pidC, WEXITSTATUS(status));
	}
	while (1)  /* bucle infinito   */
	{
		sleep(10);
	}
	return 0;
}