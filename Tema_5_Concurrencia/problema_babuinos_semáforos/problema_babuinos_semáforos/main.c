//
//  main.c
//  problema_babuinos_semáforos
//
//  Created by Vicente Cubells on 19/10/20.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define BABUINOS 100
#define CAPACIDAD 10

pthread_mutex_t mutex_este = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_oeste = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t puente = PTHREAD_MUTEX_INITIALIZER;

/* Para Linux */
sem_t este = CAPACIDAD, oeste = CAPACIDAD;

/* Para MacOS */
//sem_t * este = CAPACIDAD, * oeste = CAPACIDAD;


int babuinos_hacia_este = 0;
int babuinos_hacia_oeste = 0;

int babuinos_en_el_puente = 0;

void * babuino_este(void *);
void * babuino_oeste(void *);

int main(int argc, const char * argv[]) {
    
    srand((unsigned int) time(NULL));
    
    /* Inicializar semáforos en Linux */
    sem_init(&este, 0, CAPACIDAD);
    sem_init(&oeste, 0, CAPACIDAD);
    
    /* Para MacOS */
    // este = sem_open("este", O_CREAT, 777, CAPACIDAD);
    // oeste = sem_open("oeste", O_CREAT, 777, CAPACIDAD);
    
    
    /* Crear a los babuinos */
    pthread_t * babuinos = (pthread_t *) malloc (sizeof(pthread_t) * BABUINOS);
    
    int babuinos_creados = 0;
    
    int direccion = 0;
    
    /* Crear a los babuinos */
    while (babuinos_creados < BABUINOS) {
        direccion = rand() % 2;
        
        if (direccion == 0) {
            pthread_create(babuinos+babuinos_creados, NULL, babuino_este, NULL);
        }
        else {
            pthread_create(babuinos+babuinos_creados, NULL, babuino_oeste, NULL);
        }
        
        ++babuinos_creados;
    }
    
    /* Adjuntar los hilos */
    for (pthread_t * aux = babuinos; aux < (babuinos+BABUINOS); ++aux) {
        pthread_join(*aux, NULL);
    }
    
    free(babuinos);
    
    /* Liberar los recursos en Linux */
    sem_destroy(&este);
    sem_destroy(&oeste);

    /* En MacOS*/
    // sem_close(este);
    // sem_close(oeste);
    
    pthread_exit(NULL);
}

void * babuino_este(void * arg)
{
    sem_wait(&este);
                
    //pthread_mutex_lock(&mutex_este);
    
    ++babuinos_hacia_este;
    
    /* Babuino llega al este */
    printf("(E) --> Llega un babuino hacia el este (hay %d)\n", babuinos_hacia_este);
    
    if (babuinos_hacia_este == 1) {
        pthread_mutex_lock(&puente);
    }
    
    pthread_mutex_unlock(&mutex_este);
    
    
    /* Babuino cruza el puente */
    printf("(E) --> Cruzando un babuino hacia el este\n");
    //usleep(300);
    
    pthread_mutex_lock(&mutex_este);
    
    --babuinos_hacia_este;
    
    if (babuinos_hacia_este == 0) {
        pthread_mutex_unlock(&puente);
    }
    
    /* Babuino sale del puente */
    printf("(E) --> Sale un babuino hacia el este (quedan %d)\n", babuinos_hacia_este);
    
    pthread_mutex_unlock(&mutex_este);

    sem_post(&este);
    
    pthread_exit(NULL);
}

void * babuino_oeste(void * arg)
{
    sem_wait(&oeste);
                
    pthread_mutex_lock(&mutex_oeste);
    
    ++babuinos_hacia_oeste;
    
    /* Babuino se sube al puente */
    printf("(O) --> Llega un babuino hacia el oeste (hay %d)\n", babuinos_hacia_oeste);
    
    if (babuinos_hacia_oeste == 1) {
        pthread_mutex_lock(&puente);
    }
    
    pthread_mutex_unlock(&mutex_oeste);
    
    
    /* Babuino cruza el puente */
    printf("(O) --> Cruzando un babuino hacia el oeste\n");
    //usleep(300);
    
    pthread_mutex_lock(&mutex_oeste);
    
    --babuinos_hacia_oeste;
    
    if (babuinos_hacia_oeste == 0) {
        pthread_mutex_unlock(&puente);
    }
    
    /* Babuino sale del puente */
    printf("(O) --> Sale un babuino hacia el oeste (quedan %d) \n", babuinos_hacia_oeste);
    
    pthread_mutex_unlock(&mutex_oeste);

    sem_post(&oeste);
    
    pthread_exit(NULL);
}

