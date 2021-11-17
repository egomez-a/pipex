/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:02:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/17 10:39:54 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int var = 25;
// Declaro una variable, que será el valor cuando empieza el proceso. 

int main (void)
{
	pid_t pidC;
	printf(" ** Proceso PID = %d comienza **\n", getpid());
	// fork();
	// Esta función fork genera un proceso hijo
	// este proceso hijo es un duplicado del padre 
	// los dos procesos tienen PIDs diferentes y corren en espacios de memoria diferentes
	
	// El retorno de la función fork() es:  
	//   Retorno al padre: PID del hijo
	//   Retorno al hijo: 0
	
	// Si hay errores
	// 	Retorno al padre: -1
	// 	el hijo no es creado
	

	pidC = fork();
	// La variable pid_t es como un entero con signo, usada para PIDs. 
	// el valor que se le retorna al padre es un entero positivo, el del hijo.
	
	printf(" ** Proceso con PIDs = %d ejecutandose. La variable pidC = %d **\n", getpid(), pidC);
	
	if (pidC > 0)
	{
		var = 51;  /* proceso padre */
	}
	else if (pidC == 0)
	{
		var = 13;   /* proceso hijo */
	}
	else /* error */ 
	{
		
	}
	
	while (1)   /* ejecuta en bucle infinito   */
	{
		sleep(2);
		printf(" ** Proceso PID = %d ejecutandose. La variable Var = %d **\n", getpid(), var);
	}
	// podemos saber el proceso si es padre o hijo con esta variable pidC.
	
	return 0;
}
