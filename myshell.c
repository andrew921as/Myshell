#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int f=-1;

int main(int argc, char *argv[])
{	
	char command[256];
	char **comando;
	char primera[10];
	int i;
	int back;
	pid_t pid;
	int direcciones[30];
	int contadorhijos=0;
	
	while (1)
	{	
		printf("Usuario@Usuario:~$ ");
		leer_de_teclado(256, command);
		if (strcmp(command, "salir") == 0)
			break;
		if (strcmp(command, "tareas") == 0)
		{
				while(contadorhijos<=f){

					printf("[%d] - %d\n",contadorhijos ,direcciones[contadorhijos++]);

				}
					contadorhijos=0;
					continue;
	
		}
		comando = de_cadena_a_vector(command);
		//-------------------------------------------------------
		// Editamos nosotros
		strncpy(primera, comando[0], strlen(*comando));
		
		i = 0;	
		while (comando[i])
		{
			i++;
		}
		
		//Evaluar si el proceso se corre en segundo plano. 
		if (strcmp(comando[i - 1], "&") == 0)
		{
			comando[i - 1] = NULL;
			back = 1;
			
			//Contador para agregar un espacio al hijo
			f=f+1;
			
		}else{
			back = 0;
		}

		//-------------------------------------------------------
		//CREACION DEL HIJO
		pid = fork();	
		assert(pid >= 0);
		if (pid == 0){
			execvp(comando[0], comando);
		}
		else {
			//Validamos el proceso en background 
			if (back != 1)
			{
				wait(NULL);
			}else{
				sleep(1);
				direcciones[f]=pid;
			
			}			
		}
		
	}
	return 0;
}
