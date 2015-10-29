//
//  main.c
//  ejemplo_propiedades_hilos
//
//  Created by Vicente Cubells Nonell on 29/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

pthread_key_t tsd;

typedef struct
{
    int tid;
    char nombre[25];
} param;


void * hilo(void * arg)
{
    struct sched_param sp;
    int algoritmo;
    
    param * valores = (param * ) arg;
    
    pthread_t tid = pthread_self();
    
    pthread_getschedparam(tid, &algoritmo, &sp);
    printf("Algoritmo = %d, Prioridad = %d \n",
           algoritmo, sp.sched_priority);
    
    algoritmo = SCHED_RR;
    sp.sched_priority = 5;
    
    pthread_setschedparam(tid, algoritmo, &sp);
    printf("Algoritmo = %d, Prioridad = %d \n",
           algoritmo, sp.sched_priority);
    
    
    pthread_setspecific(tsd, (void *) &valores->tid);
    
    int * numero = (int *) pthread_getspecific(tsd);
    
    printf("TSD en %s = %d antes de modificar \n", valores->nombre, *numero);
    
    *numero = rand() % 100;
    
    pthread_setspecific(tsd, (void *) numero);
    
    numero = (int *) pthread_getspecific(tsd);
    
    printf("TSD en %s (%zd) = %d antes de modificar \n",
           valores->nombre,
           tid,
           *numero);
    
    pthread_exit(NULL);
}

int main(int argc, const char * argv[])
{
    
    pthread_t tid1, tid2;
    param p1, p2;
    pthread_attr_t attr;
    int detachstate, scope, sched, algoritmo;
    size_t stacksize;
    
    
    p1.tid = 1;
    strcpy(p1.nombre, "Hilo 1");
    
    p2.tid = 2;
    strcpy(p2.nombre, "Hilo 2");
    
    pthread_key_create(&tsd, NULL);
    
    pthread_attr_init(&attr);
    
    pthread_attr_getdetachstate(&attr, &detachstate);
    pthread_attr_getscope(&attr, &scope);
    pthread_attr_getstacksize(&attr, &stacksize);
    pthread_attr_getschedpolicy(&attr, &algoritmo);
    pthread_attr_getinheritsched(&attr, &sched);
    
    printf("Hilo 1 creado con valores siguientes: \n");
    
    printf("Valores iniciales de atributos: \n");
    printf("DETACHSTATE = %d \n", detachstate);
    printf("SCOPE = %d \n", scope);
    printf("STACKSIZE = %zu bytes\n", stacksize);
    printf("SCHEDPOLICY = %d \n", algoritmo);
    printf("INHERSCHED = %d \n", sched);
    
    pthread_create(&tid1, &attr, hilo, (void *) &p1);
    
    
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
    pthread_attr_setinheritsched(&attr, PTHREAD_INHERIT_SCHED);
    
    printf("Hilo 2 creado con valores siguientes: \n");
    
    pthread_attr_getdetachstate(&attr, &detachstate);
    pthread_attr_getscope(&attr, &scope);
    pthread_attr_getstacksize(&attr, &stacksize);
    pthread_attr_getschedpolicy(&attr, &algoritmo);
    pthread_attr_getinheritsched(&attr, &sched);
    
    printf("Valores iniciales de atributos: \n");
    printf("DETACHSTATE = %d \n", detachstate);
    printf("SCOPE = %d \n", scope);
    printf("STACKSIZE = %zu bytes\n", stacksize);
    printf("SCHEDPOLICY = %d \n", algoritmo);
    printf("INHERSCHED = %d \n", sched);
    
    pthread_create(&tid2, &attr, hilo, (void *) &p2);
    
    if (pthread_equal(tid1, tid1)) {
        printf(" Son iguales \n");
    }
    else {
        printf("Son diferentes \n");
    }
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    pthread_key_delete(tsd);
    
    pthread_attr_destroy(&attr);
    
    pthread_exit(NULL);
    
    return 0;
}

