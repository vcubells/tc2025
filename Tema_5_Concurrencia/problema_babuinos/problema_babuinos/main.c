//
//  main.c
//  problema_babuinos
//
//  Created by Vicente Cubells on 19/10/20.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BABUINOS 100

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t este = PTHREAD_COND_INITIALIZER;
pthread_cond_t oeste = PTHREAD_COND_INITIALIZER;

int babuinos_hacia_este = 0;
int babuinos_hacia_oeste = 0;

int babuinos_en_el_puente = 0;

void * babuino_este(void *);
void * babuino_oeste(void *);

int main(int argc, const char * argv[]) {
    
    srand((int) time(NULL));
    
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
    
    return 0;
}

void * babuino_este(void * id)
{
    /* Verifica si el puente está vacío o
     * está ocupado por babuinos en el mismo sentido
     * Si está vacío, o van en el mismo sentido, avanza
     */
    printf("(E) Llega un babuino hacia el este\n");
    
    pthread_mutex_lock(&mutex);
    
    if (babuinos_en_el_puente == 0 || babuinos_hacia_este > 0) {
        /* Babuino se sube al puente */
        printf("(E) --> Entra un babuino hacia el este\n");
        ++babuinos_hacia_este;
        
        ++babuinos_en_el_puente;
        
        pthread_mutex_unlock(&mutex);
        
        /* Simular un tiempo de cruce */
        usleep(300);
        
        pthread_mutex_lock(&mutex);
        /* Babuino sale del puente */
        --babuinos_hacia_este;
        
        --babuinos_en_el_puente;
        
        printf("(E) Sale un babuino hacia el este -->\n");
        
        if (babuinos_en_el_puente == 0) {
            pthread_cond_broadcast(&oeste);
        }
        
    }
    /*
     * Si está ocupado el puente por babuinos en sentido
     * contrario, espera
     */
    else {
        /* El babuino no puede pasar, tiene que esperar */
        
        printf("(E) Babuino hacia el este se va a dormir \n");
        pthread_cond_wait(&este, &mutex);
        printf("(E) Babuino hacia el este se despertó \n");
    }
    
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}


void * babuino_oeste(void * id)
{
    /* Verifica si el puente está vacío o
     * está ocupado por babuinos en el mismo sentido
     * Si está vacío, o van en el mismo sentido, avanza
     */
    printf("(O) Llega un babuino hacia el oeste\n");
    
    pthread_mutex_lock(&mutex);
    
    if (babuinos_en_el_puente == 0 || babuinos_hacia_oeste > 0) {
        /* Babuino se sube al puente */
        printf("(O) --> Entra un babuino hacia el oeste\n");
        ++babuinos_hacia_oeste;
        
        ++babuinos_en_el_puente;
        
        pthread_mutex_unlock(&mutex);
        
        /* Simular un tiempo de cruce */
        usleep(300);
        
        pthread_mutex_lock(&mutex);
        /* Babuino sale del puente */
        --babuinos_hacia_oeste;
        
        --babuinos_en_el_puente;
        
        printf("(O) Sale un babuino hacia el oeste -->\n");
        
        if (babuinos_en_el_puente == 0) {
            pthread_cond_broadcast(&este);
        }
        
    }
    /*
     * Si está ocupado el puente por babuinos en sentido
     * contrario, espera
     */
    else {
        /* El babuino no puede pasar, tiene que esperar */
        
        printf("(E) Babuino hacia el oeste se va a dormir \n");
        pthread_cond_wait(&oeste, &mutex);
        printf("(E) Babuino hacia el oeste se despertó \n");
        
    }
    
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}
