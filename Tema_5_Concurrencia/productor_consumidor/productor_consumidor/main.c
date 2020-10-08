//
//  main.c
//  productor_consumidor
//
//  Created by Vicente Cubells Nonell on 08/10/20.
//  Copyright © 2020 Vicente Cubells Nonell. All rights reserved.
//

/*
  Solución al problema del ptoductor-consumidor utilizando variables de condición
  - Buena solución porque no tiene espera activa
  - Además, brinda sincronización (a quien le corresponde el turno)
  - Funciones pthread_cond_wait() y pthread_cond_signal()
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 10
#define N 100

int elementos[BSIZE];

int in = 0;
int out = 0;

int total = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void * productor(void *);
void * consumidor(void *);

int main(int argc, const char * argv[]) {
    
    pthread_t produce, consume;
    
    srand(time(NULL));
    
    /* Crear el hilo productor */
    produce = pthread_create(&produce, NULL, productor, NULL);
    
    /* Crear el hilo consumidor */
    produce = pthread_create(&consume, NULL, consumidor, NULL);
    

    /* Esperar a que los hilos terminen */
    pthread_join(produce, NULL);
    
    pthread_join(consume, NULL);
    
    return 0;
}

void * productor(void * arg)
{
    int i = 0;
    
    while (i < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total < BSIZE) {
            
            /* Produce un elemento */
            
            elementos[in] = i;
            
            printf(" +++ Se produjo el elemento %d\n", elementos[in]);
            
            ++i;
            
            in += i % BSIZE;
            ++total;
            
            if (total == 1) {
                pthread_cond_signal(&consume_t);
            }
        }
        else {
            /* El buffer está lleno, se va a dormir */
            
            printf("zzzzz El productor se va a dormir \n");
            pthread_cond_wait(&produce_t, &mutex);
            printf("uuuuu El productor se despertó \n");
        }
        
        pthread_mutex_unlock(&mutex);
   
    }
    
    pthread_exit(NULL);
}

void * consumidor(void * arg)
{
    int i = 0;
    
    while (i < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total > 0)
        {
            /* Consume un elemento */
            
            printf(" --- Se consumió el elemento %d\n", elementos[out]);
            
            ++i;
            
            out += i % BSIZE;
            --total;
            
            if (total == BSIZE - 1) {
                pthread_cond_signal(&produce_t);
            }
            
        }
        else {
            /* El buffer está vacío, se va a dormir */
            printf("ZZZZZ El consumidor se va a dormir \n");
            pthread_cond_wait(&consume_t, &mutex);
            printf("UUUUU El consumidor se despertó \n");
        }
        
        pthread_mutex_unlock(&mutex);
 
    }
    
    pthread_exit(NULL);
}

