//
//  main.c
//  multiples_productores_consumidores
//
//  Created by Vicente Cubells Nonell on 22/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BSIZE 10
#define N 100

#define PRODUCTORES 5
#define CONSUMIDORES 3

int elementos[BSIZE];

int in = 0;
int out = 0;

int total = 0;

int producidos = 0, consumidos = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consume_t = PTHREAD_COND_INITIALIZER;
pthread_cond_t produce_t = PTHREAD_COND_INITIALIZER;

void * productor(void *);
void * consumidor(void *);

int main(int argc, const char * argv[]) {
    
    srand((int) time(NULL));
    
    int nhilos = PRODUCTORES + CONSUMIDORES;
    
    pthread_t * obreros = (pthread_t *) malloc (sizeof(pthread_t) * nhilos);
    
    int indice = 0;
    
    pthread_t * aux;
    
    /* Crear los productores */
    for (aux = obreros; aux < (obreros+PRODUCTORES); ++aux) {
        printf("--- Creando el productor %d ---\n", ++indice);
        pthread_create(aux, NULL, productor, (void *) indice);
    }
    
    /* Crear los consumidores */
    indice = 0;
    
    for (; aux < (obreros+nhilos); ++aux) {
        printf("--- Creando el consumidor %d ---\n", ++indice);
        pthread_create(aux, NULL, consumidor, (void *) indice);
    }
    
    /* Adjuntar los hilos */
    for (aux = obreros; aux < (obreros+nhilos); ++aux) {
        pthread_join(*aux, NULL);
    }
    
    free(obreros);
    
    return 0;

}

void * productor(void * arg)
{
    int id = (int) arg;
    
    while (producidos < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total < BSIZE) {
            
            /* Produce un elemento */
            
            elementos[in] = producidos;
            
            printf(" +++ (Productor %d) Se produjo el elemento %d\n", id, elementos[in]);
            
            ++producidos;
            
            ++in;
            in %= BSIZE;
            ++total;
            
            if (total == 1) {
                pthread_cond_broadcast(&consume_t);
            }
        }
        else {
            /* El buffer está lleno, se va a dormir */
            
            printf("zzzzz (Productor %d) se va a dormir \n", id);
            pthread_cond_wait(&produce_t, &mutex);
            printf("uuuuu (Productor %d) se despertó \n", id);
        }
        
        pthread_mutex_unlock(&mutex);
        
    }
    
    pthread_exit(NULL);
}

void * consumidor(void * arg)
{
    int id = (int) arg;
    
    while (consumidos < N) {
        
        /* Asumir que trabajan a diferentes velocidades */
        
        usleep(rand() % 500);
        
        pthread_mutex_lock(&mutex);
        
        if (total > 0)
        {
            /* Consume un elemento */
            
            printf(" --- (Consumidor %d) Se consumió el elemento %d\n", id, elementos[out]);
            
            ++consumidos;
            
            ++out;
            out %= BSIZE;
            --total;
            
            if (total == BSIZE -1) {
                pthread_cond_broadcast(&produce_t);
            }
            
        }
        else {
            /* El buffer está vacío, se va a dormir */
            printf("ZZZZZ (Consumidor %d) se va a dormir \n", id);
            pthread_cond_wait(&consume_t, &mutex);
            printf("UUUUU (Consumidor %d) se despertó \n", id);
        }
        
        pthread_mutex_unlock(&mutex);
        
    }
    
    pthread_exit(NULL);
}

