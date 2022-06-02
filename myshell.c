#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char *argv[])
{
	char command[256];
	char **comando;
	char primera[10];
	int i;
	int back;
	
	while (1)
	{
		printf("> ");
		leer_de_teclado(256, command);
		if (strcmp(command, "salir") == 0)
			break;
		comando = de_cadena_a_vector(command);
		//-------------------------------------------------------
		// Editamos nosotros
		printf("strlen(comando) = %ld\n", strlen(*comando));
		printf("%s \n", comando[1]);
		strncpy(primera, comando[0], strlen(*comando));

		i = 0;
		while (comando[i])
		{
			printf("%s\n", comando[i++]);
		}
		//Evaluar si el proceso se corre en segundo plano. 
		if (strcmp(comando[i - 1], "&") == 0)
		{
			comando[i - 1] = NULL;
			back = 1;
			
		}
		if (strcmp(comando[0], "fg") == 0)
		{
			back=0;
		}

		//-------------------------------------------------------
		//CREACION DEL HIJO
		int rc = fork();	
		assert(rc >= 0);
		if (rc == 0){
			printf("soy el hijo num ");
			execvp(comando[0], comando);
		}
		else {
			//Validamos el proceso en background 
			if (back != 1)
			{
				wait(NULL);
			}
		}
		
	}
	return 0;
}
