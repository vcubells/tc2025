//
//  main.c
//  ejemplo_señales_entre_hilos
//
//  Created by Vicente Cubells Nonell on 29/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void * Hilo1 (void * id)
{
    sigset_t set;
    int sig;
    
    sigemptyset(&set);
    
    sigaddset(&set, SIGUSR1);
    
    while (1)
    {
        sigwait(&set, &sig);
        if (sig == SIGUSR1)
            printf("SOy el hilo 1 y recibí la señal SIGUSR1...\n");
    }
}

void * Hilo2 (void * id)
{
    sigset_t set;
    int sig;
    
    pthread_t * tid = (pthread_t *) id;
    
    sigemptyset(&set);
    
    sigaddset(&set, SIGINT);
    
    while (1)
    {
        sigwait(&set, &sig);
        if (sig == SIGINT) {
            printf("SOy el hilo 2 y le mando una señal SIGUSR1 al hilo 1 ...\n");
            pthread_kill(*tid, SIGUSR1);
        }
    }
}


int main(int argc, char **argv)
{
    pthread_t tid1, tid2;
    sigset_t set;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR1);
    
    /* Bloquear señales en el hilo principal */
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    
    
    pthread_create(&tid1, NULL, Hilo1, NULL);
    pthread_create(&tid2, NULL, Hilo2, (void *) &tid1);
    
    while (1)
    {
        printf("Soy el hilo principal...\n");
        sleep(1);
    }
    
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    
    
    return 0;
}

