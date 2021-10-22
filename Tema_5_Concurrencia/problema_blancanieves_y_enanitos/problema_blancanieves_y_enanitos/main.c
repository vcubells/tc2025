//
//  main.c
//  problema_blancanieves_y_enanitos
//
//  Created by Vicente Cubells on 25/10/20.
//
/* Blancanieves y 7 enanitos */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define ENANOS 7
#define SILLAS 4
#define NHILOS ENANOS + 1

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

sem_t silla, turno;
int esperando;

void *  enanito(void *);
void *  blancanieves(void *);

int main(int argc, const char * argv[])
{
    pthread_t hilos[NHILOS];
    int result, i;
    
    sem_init(&silla, 0, SILLAS);
    sem_init(&turno, 0, 0);
    esperando = 0;
    
    /* Crear Blancanieves */
    result = pthread_create(&hilos[0], NULL, blancanieves, NULL);
    if (result)
        printf("Error al crear a Blancanieves \n");
    
    /* Crear enanitos */
    for (i = 1; i <= ENANOS; ++i )
    result = pthread_create(&hilos[i], NULL, enanito, (void *)&i);
    if (result)
        printf("Error al crear el enano %d \n", i);
        
        
    /* Esperar a que terminen los hilos */
    for(i = 0; i < NHILOS; ++i)
    {
        result = pthread_join(hilos[i], NULL);
        if (result)
            printf("Error al adjuntar el hilo %d \n", i);
    }
    
    /* Garantizar que se liberen los recursos */
    sem_destroy(&silla);
    sem_destroy(&turno);
    pthread_exit(NULL);
}

void *  enanito(void * arg)
{
    //usleep(rand()%50);
    int * idptr = (int *) arg;
    int id = *idptr;
    
    while(1)
    {
        printf("Enano %d dice 'Estoy trabajando en la mina'\n", id);
        sleep(rand() % 3);
        printf("Enano %d dice 'Quiero sentarme a comer'\n", id);
        sem_wait(&silla);
        printf("Enano %d dice 'Ya estoy sentado, sírveme'\n", id);
        pthread_mutex_lock(&mutex);
        esperando += 1;
        pthread_mutex_unlock(&mutex);
        /* Blancanieves le sirve */
        sem_wait(&turno);
        pthread_mutex_lock(&mutex);
        esperando -= 1;
        pthread_mutex_unlock(&mutex);
        printf("Enano %d dice 'Ya me tocó el turno, estoy comiendo'\n", id);
        sleep(rand()%3);
        printf("Enano %d dice 'Ya terminé de comer, dejo la silla vacía'\n", id);
        sem_post(&silla);
        printf("Enano %d dice 'Me voy a la mina'\n", id);
    }
}

void *  blancanieves(void * arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if (esperando == 0) // No hay ningún enanito esperando
        {
            pthread_mutex_unlock(&mutex);
            printf("Blancanieves dice 'Me voy de paseo'\n");
            sleep(rand()%3);
        }
        else { // Hay algún enanito esperando
            pthread_mutex_unlock(&mutex);
            printf("Blancanieves dice 'Estoy cocinando para un enano'\n");
            printf("Blancanieves dice 'La comida ya está lista'\n");
            sem_post(&turno);
        }
    }
}
