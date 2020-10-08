//
//  main.c
//  solucion_problema_variable_global
//
//  Created by Vicente Cubells Nonell on 08/10/20.
//  Copyright © 2020 Vicente Cubells Nonell. All rights reserved.
//

/*
  Solución al problema de la región crítica utilizando bloqueos con mutexes
   - Funciones pthread_mutex_lock() y pthread_mutex_unlock()
   - Inicialización estática de los mutexes con la macro PTHREAD_MUTEX_INITIALIZER
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define OPERACIONES 100
#define NHILOS 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int suma = 0;
int resta = OPERACIONES;

void * sumar(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
    for (i = 0; i < OPERACIONES; ++i) {
        
        /* Inicia Región crítica */
        pthread_mutex_lock(&mutex); // DOWN
        
        temp = suma;
        /* Podría haber un cambio de contexto */
        usleep(rand() % 300);
        
        suma = temp + 1;
        
        temp = resta;
        
        usleep(rand() % 300);
        
        resta = temp + 1 ;
        
        /* Termina región crítica */
        pthread_mutex_unlock(&mutex); // UP
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
        pthread_mutex_lock(&mutex);
        
        temp = suma;
        
        /* Podría haber un cambio de contexto */
        usleep(rand() % 300);
        suma = temp - 1;
        
        temp = resta;
        
        usleep(rand() % 300);
        
        resta = temp - 1 ;
        
        /* Termina región crítica */
        pthread_mutex_unlock(&mutex);
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
    
    pthread_create(tid, NULL, sumar, (void *)0);
    pthread_create(tid+1, NULL, restar, (void *)1);
    
    printf("Se crearon %d hilos ...\n", nhilos);
    
    for (i = 0; i < nhilos; ++i) {
        pthread_join(*(tid+i), NULL);
        printf("Se unió el hilo %d con TID = %d...\n", i, (int) *(tid+i));
    }
    
    printf("Soy el proceso principal y ya terminaron todos los hilos...\n");
    
    printf("Suma = %d y Resta = %d \n", suma, resta );
    
    free(tid);
    
    return 0;
}

