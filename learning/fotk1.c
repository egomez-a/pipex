/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fotk1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egomez-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:02:40 by egomez-a          #+#    #+#             */
/*   Updated: 2021/11/10 14:36:45 by egomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int var = 22;
// declaro una variable, que será el valor cuando empieza el proceso. 

int main (void)
{
	
	pid_t pidC;
	printf(" ** Proceso PID = %d comienza **\n", getpid());
	// fork();
	// Esta función fork genera un proceso hijo
	// este proceso hijo es un duplicado del padre 
	// los dos procesos tienen PIDs diferentes y corren en espacios de memoria diferentes
	
	// Retorno de fork es:  
	//   Retorno al padre: PID del hijo
	//   Retorno al hijo: 0
	
	// Si hay errores
	// 	Retorno al padre -1
	// 	el hijo no es creado
	

	pidC = fork();
	// La variable pid_t es como un entero con signo, para PIDs. 
	// el valor que se le retorna al padre es un entero positivo, el del hijo.
	
	printf(" ** Proceso PID = %d, pidC = %d ejecutandose **\n", getpid(), pidC);
	
	if (pidC > 0)
	{
		var = 44;  /* proceso padre */
	}
	else if (pidC == 0)
	{
		var = 33;   /* proceso hijo */
	}
	else /* error */ 
	{
		
	}
	while (1)   /* ejecuta en bucle infinito   */
	{
		sleep(2);
		printf(" ** Proceso PID = %d, Var = %d ejecutandose **\n", getpid(), var);
	}
	// podemos saber el proceso si es padre o hijo con esta variable pidC.
	
	return 0;
}
