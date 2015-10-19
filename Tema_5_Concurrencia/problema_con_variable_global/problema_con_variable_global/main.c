//
//  main.c
//  problema_con_variable_global
//
//  Created by Vicente Cubells Nonell on 19/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

//
//  main.c
//  t5c3e1
//
//  Created by Vicente Cubells Nonell on 03/10/13.
//  Copyright (c) 2013 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define OPERACIONES 100
#define NHILOS 2

int suma = 0;

void * sumar(void * arg)
{
    int tid = (int) arg;
    int i;
    
    int temp;
    
    for (i = 0; i < OPERACIONES; ++i) {

        temp = suma;
        /* Podría haber un cambio de contexto */
        suma = suma + 1;
    }
    
    pthread_exit(0);
}

void * restar(void * arg)
{
    int tid = (int) arg;
    int i;

    int temp;
    
    for (i = 0; i < OPERACIONES; ++i) {
        
        temp = suma;
        /* Podría haber un cambio de contexto */
        suma = suma - 1;
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
    
    printf("Suma = %d y debía ser %d \n", suma, 0 );
    
    free(tid);
    
    return 0;
}

