#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"
#include <stdlib.h>


int main(int argc, char *argv[])
{	
	int f=-1;
	char command[256];
	char **comando;
	char primera[10];
	int i;
	int back;
	pid_t pid;
	int direcciones[30];
	int contadorhijos=0;
	int objetivo=0;
	int posicion=0;
	int cont=1;
	
	while (1)
	{	
		printf("Usuario@Usuario:~$ ");
		leer_de_teclado(256, command);


		if (strcmp(command, "salir") == 0)
			break;
		if (strcmp(command, "tareas") == 0)
		{
				while(contadorhijos<=f)
				{
					if (direcciones[contadorhijos]!=0)
					{
						printf("[%d] - %d\n",cont++ ,direcciones[contadorhijos++]);
					}
					else 
					{
						contadorhijos++;
					}
				}
				cont=1; 
				contadorhijos=0;
				continue;
	
		}
		
		comando = de_cadena_a_vector(command);

		i = 0;	
		while (comando[i])
		{
			i++;
		}
		

		if (strcmp(comando[0], "detener") == 0)
		{
			
			objetivo = strtol(comando[i-1],NULL,10);
			printf("objetivo: %d \n",objetivo);
			

			
			while (posicion<=f)
			{	
		
				printf("la direccion que quiero: %d \n",direcciones[posicion]);
				printf(" mi objetivo%d \n",objetivo);
				if (direcciones[posicion]==objetivo)
				{
					printf("QUE SE DICE  \n");
					kill (objetivo,SIGKILL); 
					direcciones [posicion]=0;
					break;
					
				}
				
				posicion++;
			}
			

			printf("mi posicion es %d \n",posicion);
			continue;
		}
		//-------------------------------------------------------
		// Editamos nosotros
		strncpy(primera, comando[0], strlen(*comando));
		
// AQUI YO TENIA UN WHILE que tenia la i

		//Evaluar si el proceso se corre en segundo plano. 
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
