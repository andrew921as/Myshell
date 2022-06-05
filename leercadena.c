/*
 * Este programa muestra como leer varias palabras del teclado (stdin)
 * Codigo tomado de: https://www.programiz.com/c-programming/c-strings
 *
 * Modificado por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Fecha: 2021-02-26
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leercadena.h"

/**
 * Lee un cadena por teclado.
 * @param[in] size tamano del buffer representado en cadena
 * @param[in] cadena buffer donde se almacenara lo leido de teclado
 * @param[out] tamano de la cadena leida
*/

int leer_de_teclado(int size, char* cadena) { 
  fgets(cadena, size, stdin);
  cadena[strlen(cadena) - 1] = '\x0';

  return strlen(cadena);
} 

/*
  GLOSARIO DE C
  assert: se encarga de devolver errores y diagnosticar el programa
  char** Es un puntero al puntero de una cadena de caracteres
  strtok: divide una cadena en tokens (cadena "a dividir", delim "delimitador por el cual va a dividir la cadena")
  tokens: Forma en la que esta divida la cadena (primer parametro de strtok)
  delim: Cadena delimitadora (Segundo parametro de strtok)
  malloc: asignacion dinamica de memoria(se le asigna un bloque de memoria al programa)
  strdup: es una copia del token
  strncpy: Copia del string
*/

char** de_cadena_a_vector(char* cadena) {
  int i;
  char *token;
  char *delim = " ";
  char** resultado;

  resultado = (char**)malloc(sizeof(char*));
  assert(resultado != NULL);
  i = 0;
  token = strtok(cadena,delim);
  while ( token != NULL) {
    int cad_longitud;
    char **result_temp;
    cad_longitud = strlen(token) + 1;
    // Copiar token en la posicion 'i'
    resultado[i] = strdup(token);
    //printf("|%s|\n",resultado[i]); fflush(stdout);
    // En busca de la proxima cadena
    token = strtok(NULL, delim);
    i++;
    result_temp = realloc(resultado, (i + 1)  * sizeof(*resultado));
    assert(result_temp != NULL);
    resultado = result_temp;
  }

  resultado[i] = NULL;
  return resultado;
}

