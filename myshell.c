#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "leercadena.h"

int main(int argc, char* argv[]) {
    	char command[256];
    	char **comando;
		char primera[10];
		 
    	while (1) {
            	printf("> ");
            	leer_de_teclado(256, command);
            	if (strcmp(command,"salir") == 0) break;
            	comando = de_cadena_a_vector(command);		
				printf( "strlen(comando) = %ld\n", strlen(*comando));
				printf("%s \n",comando[1]);
				strncpy(primera,comando[0],strlen(*comando));
				char *ultimaL[1];
            	int rc = fork();
            	assert(rc >= 0);
            	if (rc == 0)
                    	execvp(comando[0], comando);
            	else
                    	wait(NULL);
    	}
    	return 0;
}


