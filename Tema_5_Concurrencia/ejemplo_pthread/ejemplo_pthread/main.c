//
//  main.c
//  ejemplo_pthread
//
//  Created by Vicente Cubells Nonell on 15/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define N 100

typedef struct {
    int id;
    int random;
} data;

void * suma(void * arg);

int main(int argc, const char * argv[]) {
    
    int nhilos = 0;
    
    data datos;
    
    srand((unsigned) time(NULL));
    
    printf("¿Cuántos hilos quieres crear? : ");
    scanf("%d", &nhilos);
    
    /* Creando los hilos */
    pthread_t * tids = (pthread_t *) malloc(nhilos * sizeof(pthread_t));
    
    for (int i = 0; i < nhilos; ++i) {
        
        datos.id = i;
        datos.random = rand() % 1000;
        
        printf("+++ Creando el hilo %d ...\n", i);
        pthread_create((tids+i), NULL, suma,  i);
    }
    
    /* Esperar a que todos los hilos terminen */
    
    for (int i = 0; i < nhilos; ++i) {
        
        pthread_join(*(tids+i), NULL);
        
        printf("--- Terminando el hilo %d ...\n", i);
    }
    
    free(tids);
    
    return 0;
}

void * suma(void * arg)
{
    sleep(rand() %10);
    
    printf("H - Soy el hilo %d\n", arg);

    pthread_exit(NULL);
}
