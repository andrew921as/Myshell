# Myshell
En este proyecto se elaboro un shell en C tomando como base un codigo proporcionado por el profesor e implementandole procesos en segundo plano y validacion de comandos


Datos importantes para la elaboracion del programa:

#pid=fork() / pid va a tomar valores: 0 para el hijo, El PID del hijo para el padre y un numero negativo en caso de error.

#La funcion kill() tiene como parametros el PID del proceso que se quiere terminar y un campo de confirmacion.

#La palabra reservada continue; permite acbar la iteracion del bucle, no se sale del bucle como tal solo acaba la iteracion hasta el momento

Palabras propias del programa:

salir: acaba el programa, saliendose del ciclo.

tareas: Lista las tareas que se estan ejecutando en segundo plano [numero identificador][PID de la tarea]

detener PID: este comando detiene el proceso que se selecciono PID= numero del PID de la tarea que se quiere detener.

