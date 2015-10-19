//
//  main.c
//  problema_inversion_mutexes
//
//  Created by Vicente Cubells Nonell on 19/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define OPERACIONES 100
#define NHILOS 2

pthread_mutex_t mutex_s = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_r = PTHREAD_MUTEX_INITIALIZER;

int suma = 0;
int resta = OPERACIONES;

void * sumar(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
    for (i = 0; i < OPERACIONES; ++i) {
        
        /* Inicia Región crítica */
        pthread_mutex_lock(&mutex_s); // DOWN
        
        temp = suma;
        /* Podría haber un cambio de contexto */
        suma = suma + 1;
        
        pthread_mutex_lock(&mutex_r);
        resta = resta + 1;
        pthread_mutex_unlock(&mutex_r);
        
        /* Termina región crítica */
        pthread_mutex_unlock(&mutex_s); // UP
    }
    
    pthread_exit(0);
}

void * restar(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
    for (i = 0; i < OPERACIONES; ++i) {
        
        /* Inicia Región crítica */
        pthread_mutex_lock(&mutex_s);
        
        temp = suma;
        /* Podría haber un cambio de contexto */
        
        suma = suma - 1;
        
        pthread_mutex_lock(&mutex_r);
        
        resta = resta - 1 ;
        
        pthread_mutex_unlock(&mutex_r);
        
        /* Termina región crítica */
        pthread_mutex_unlock(&mutex_s);
    }
    
    
    pthread_exit(0);
}

int main(int argc, const char * argv[])
{
    
    pthread_t * tid;
    int nhilos;
    int i;
    
    nhilos = NHILOS;
    
    tid = malloc(nhilos * sizeof(pthread_t));
    
    printf("Creando hilos ...\n");
    
    pthread_create(tid, NULL, sumar, (void *)0);
    pthread_create(tid+1, NULL, restar, (void *)1);
    
    printf("Se crearon %d hilos ...\n", nhilos);
    
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("Se unió el hilo %d con TID = %d...\n", i, *(tid+i));
    }
    
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    printf("Suma = %d y Resta = %d \n", suma, resta );
    
    free(tid);
    
    return 0;
}


