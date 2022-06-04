#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int f=0;

int main(int argc, char *argv[])
{	
	int f=0;
	char command[256];
	char **comando;
	char primera[10];
	int i;
	int back;
	pid_t pid;
	char direcciones[30];
	int *memoria;
	int pru; 
	//prueba del pipe
    int fd[2];

	while (1)
	{	
		printf("Usuario@Usuario:~$ ");
		leer_de_teclado(256, command);
		if (strcmp(command, "salir") == 0)
			break;
		comando = de_cadena_a_vector(command);
		//-------------------------------------------------------
		// Editamos nosotros
		//printf("strlen(comando) = %ld\n", strlen(*comando));
		//printf("%s \n", comando[1]);
		strncpy(primera, comando[0], strlen(*comando));

		i = 0;
		
		while (comando[i])
		{
			//printf("%s\n", comando[i++]);
			i++;
		}
		
		//Evaluar si el proceso se corre en segundo plano. 
		if (strcmp(comando[i - 1], "&") == 0)
		{
			comando[i - 1] = NULL;
			back = 1;
			
			//Contador para agregar un espacio al hijo

			printf("%d\n",f);
			f=f+1;
			printf("%d\n",f);
			
		}

		//-------------------------------------------------------
		pipe(fd);
		//CREACION DEL HIJO
		pid = fork();	
		assert(pid >= 0);
		if (pid == 0){
			printf("HOLAAAA MIRAAAA SOY UN NIÑOOOOOO - %d\n", getpid());
			/*
			direcciones[f]=getpid();
			printf("Me imprimi desde la direccion - %d\n", direcciones[f]);

			for (int l=0; l<=f; l++)
		{
			printf("%d\n", direcciones[l]);
		}
		*/
			close(fd[0]);
			
			write(fd[1],"205",sizeof(getpid()));
			close(fd[1]);

			execvp(comando[0], comando);
		}
		else {
			//Validamos el proceso en background 
			if (back != 1)
			{
				printf("soy el papa num %d \n", getpid());
				wait(NULL);
			}else{
			close(fd[1]);
			read(fd[0],direcciones[f],sizeof(direcciones));
			printf("soy el padre y mi hijo tiene la direccion: - %d\n", direcciones[f]);	
			close(fd[0]);
			printf("soy el padre y mi hijo tiene la direccion: - %d\n", direcciones[f]);	
			}
		}
		
	}
	return 0;
}
