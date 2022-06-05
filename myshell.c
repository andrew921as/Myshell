#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <stdlib.h>


int main(int argc, char *argv[])
{	
	int f=-1, i, back, cont=0, posicion=0, objetivo=0, contadorhijos=0;
	char command[256];
	char **comando;
	char primera[10];
	pid_t pid;
	int direcciones[30];
	
	while (1)
	{	
		printf("Usuario@Usuario:~$ ");
		leer_de_teclado(256, command);

		if (strcmp(command, "salir") == 0)
			break;

		// Si el comando ingresado es "tareas", devuelve una lista de pids de los procesos ejecutados en segundo plano
		if (strcmp(command, "tareas") == 0)
		{
				
				while(contadorhijos<=f)
				{
					
					if (direcciones[contadorhijos]!=0)
					{
						cont++;
						printf("[%d] - %d\n",cont,direcciones[contadorhijos++]);
					}
					else 
					{
						contadorhijos++;
					}
					
				}

				if (cont==0)
				{
					printf("No hay tareas ejecutandose en segundo plano\n");
				} 

				cont=0; 
				contadorhijos=0;
				continue;
		}
		
		comando = de_cadena_a_vector(command);
		i = 0;	
		while (comando[i])
		{
			i++;
		}
		
		// Si el comando ingresado es "detener" se elimina el proceso en segundo plano cuyo pid corresponda al digitado por el usuario 
		if (strcmp(comando[0], "detener") == 0)
		{
			
			objetivo = strtol(comando[i-1],NULL,10);
			
			while (posicion<=f)
			{	
				if (direcciones[posicion]==objetivo)
				{
					kill (objetivo,SIGKILL); 
					direcciones [posicion]=0;
					break;				
				}
				
				posicion++;
			}
			
			continue;
		}

		strncpy(primera, comando[0], strlen(*comando));

		//If que Evalua si el proceso se corre en segundo plano. 
		if (strcmp(comando[i - 1], "&") == 0)
		{
			comando[i - 1] = NULL;
			back = 1;
			
			//Contador para agregar un espacio al hijo
			f++; 
			
		}else{
			back = 0;
		}

		//-------------------------------------------------------

		//CREACION DEL HIJO
		pid = fork();	
		assert(pid >= 0);
		if (pid == 0)
		{
			execvp(comando[0], comando);
			if (execvp(comando[0], comando)==-1)
			{
				printf("Comando no valido\n");
				exit(EXIT_FAILURE);	
			}
		}
		else {
			//Validamos el proceso en background 
			if (back != 1)
			{
				wait(NULL);
			} else
			{
				sleep(1);
				direcciones[f]=pid;
			}			
		}
		
	}
	return 0;
}
