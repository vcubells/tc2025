//
//  main.c
//  problema_con_variable_global
//
//  Created by Vicente Cubells Nonell on 06/10/20.
//  Copyright © 2020 Vicente Cubells Nonell. All rights reserved.
//

/*
  Demostrar el problema que surge al no proteger la región crítica (variable global suma)
  cuando los procesos se ejecutan en un orden arbitrario.
   - Solución no determinista
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define OPERACIONES 100
#define NHILOS 5

/* Variable compartida */
int suma = 0;

void * sumar(void * arg)
{
    int temp;
    
    for (int i = 0; i < OPERACIONES; ++i) {
        
        /* Región crítica */
        temp = suma;
        /* Podría haber un cambio de contexto */
        usleep(rand() % 200 );
        suma = temp + 1;
        /* Termina la región crítica */
    }
    
    pthread_exit(0);
}

int main(int argc, const char * argv[])
{
    pthread_t * tid;
    int nhilos;
    int i;
    
    srand((unsigned int) time(NULL));
    
    nhilos = NHILOS;
    
    tid = malloc(nhilos * sizeof(pthread_t));
    
    printf("Creando hilos ...\n");
    
    for (i = 0; i < nhilos; ++i) {
        pthread_create(tid+i, NULL, sumar, NULL);
        printf("Se creó el hilo %d con TID = %d\n", i, (int) *(tid+i));
    }
    
    printf("Se crearon %d hilos ...\n", nhilos);
    
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("Se unió el hilo %d con TID = %d\n", i, (int) *(tid+i));
    }
    
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    printf("Suma total = %d y debía ser %d \n", suma, nhilos * OPERACIONES );
    
    free(tid);
    
    return 0;
}

