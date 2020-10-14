//
//  main.cpp
//  productor_consumidor_semáforos
//
//  Created by Vicente Cubells on 08/10/20.
//

/*
  Solución al problema del productor-consumidor utilizando semáphoros POSIX (no son parte de Pthreads)
  - 1 productor y 1 consumidor
  - Se utiliza:
   * sem_get() - Es el DOWN,
   * sem_post() - Es el UP
   * sem_init() - Inicializa un semáforo
   * sem_destroy() - Libera la memoria ocupada por el semáforo
   * sem_getvalue() - Devuelve el valor de un semáforo
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BSIZE 10
#define N 100

int elementos[BSIZE];

int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t vacio, lleno;

void * productor(void *);
void * consumidor(void *);

int main(int argc, const char * argv[]) {
    
    pthread_t produce, consume;
    
    srand((unsigned int) time(NULL));
    
    /* Inicializar semáforos */
    sem_init(&vacio, 0, BSIZE);
    sem_init(&lleno, 0, 0);
    
    /* Crear el hilo productor */
    pthread_create(&produce, NULL, productor, NULL);
    
    /* Crear el hilo consumidor */
    pthread_create(&consume, NULL, consumidor, NULL);
    

    /* Esperar a que los hilos terminen */
    pthread_join(produce, NULL);
    
    pthread_join(consume, NULL);
    
    /* Liberar los recursos */
    sem_destroy(&vacio);
    sem_destroy(&lleno);
    
    pthread_exit(NULL);
}

void * productor(void * arg)
{
    int i = 0;
    int valor;
    
    while (i < N) {
        
        sem_wait(&vacio);
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        /* Produce un elemento */
        
        elementos[in] = i;
        
        printf(" +++ Se produjo el elemento %d\n", elementos[in]);
        
        ++i;
        ++in;
        in %= BSIZE;
        
        sem_post(&lleno);
        sem_getvalue(&vacio, &valor);
        if (valor == 0) {
            printf("El buffer ya está lleno, productor tiene que esperar\n");
        }
        
        pthread_mutex_unlock(&mutex);
   
    }
    
    pthread_exit(NULL);
}

void * consumidor(void * arg)
{
    int i = 0;
    int valor;
    
    while (i < N) {
        
        sem_wait(&lleno);
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        /* Consume un elemento */
        
        printf(" --- Se consumió el elemento %d\n", elementos[out]);
        
        ++i;
        ++out;
        out %= BSIZE;
        
        sem_post(&vacio);
        sem_getvalue(&lleno, &valor);
        if (valor == 0) {
            printf("El búffer está vacío, consumidor tienen que esperar\n");
        }
            
        pthread_mutex_unlock(&mutex);
 
    }
    
    pthread_exit(NULL);
}


