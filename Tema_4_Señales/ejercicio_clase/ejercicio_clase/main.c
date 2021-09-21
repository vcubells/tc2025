//
//  main.c
//  ejercicio_clase
//
//  Created by Vicente Cubells on 21/09/21.
//

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

pid_t pidh;

void manejador(int ids)
{
    pid_t pid = getpid();
    printf("Soy %d y Recibí un SIGUSR1, voy a dormir 1 segundo...\n", pid);
    sleep(1);
    printf("Soy %d, desperté y envié un SIGUSR1\n", pid);
    kill(pidh, SIGUSR1);
}

int main(int argc, const char * argv[]) {
    
    if (signal(SIGUSR1, manejador) == SIG_ERR) {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    
    pidh = fork();
    
    if (pidh == -1) {
        printf("Error al crear el proceso hijo...\n");
        exit(-1);
    }
    else if (pidh == 0) {
        pidh = getppid();
        printf("Soy el hijo con PID %d\n", getpid());
        while (1);
    }
    else {
        printf("Soy el padre con PID %d\n", getpid());
        kill(pidh, SIGUSR1);
        while (1);
    }
    
    return 0;
}
