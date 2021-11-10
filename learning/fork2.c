/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:55:13 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/05 10:12:37 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

// este programa es para crear 5 hijos
// el bucle for es para que el padre vaya creando hijos
#define NUM_CHILD 5


/* Funcion para calcular un numero aleatorio. Semilla es srand, y el numero*/
/* está entre 0 y 255 */
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
		else if (pidC == 0)
		{
			exit(doSomething());
		}
		else 
		{
			/*error*/
		}
	}
	for(int i = 0; i < NUM_CHILD; i++)
	{
		pidC = wait(&status);
		printf("Padre de PID = %d, Hijo de PID = %d terminado, st = %d\n", getpid(), pidC, WEXITSTATUS(status));
	}
	while (1)
	{
		sleep(10);
	}
	return 0;
}