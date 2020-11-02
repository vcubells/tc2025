//
//  main.c
//  pthread_simd
//
//  Created by Vicente Cubells on 26/10/20.
//
/* Resolver el problema de la suma de vector utilizando SIMD */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int NHILOS = 4;
int N = 1000;

/* Vector de elementos */
int * vector;

/* Vector de sumas parciales */
int * sumas;

/* Variable acumuladora global */
int suma_global = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int suma()
{
    int total = 0;
    
    int * fin = vector + N;
    
    for (int * aux = vector; aux < fin; ++aux) {
        total += *aux;
    }
    
    /* Tomar el tiempo final */
    time_t t_fin = time(NULL);
    
    
    
    return total;
}

void * suma_paralela(void * tid)
{
    int id = (int *) tid;
    
    int total = 0;
    
    int elementos = N / NHILOS;
    
    int * inicio = vector + (id * elementos);
    int * fin;
    
    if (id == NHILOS-1) {
        fin = vector + N;
    }
    else {
        fin = inicio + elementos;
    }
    
    for (int * aux = inicio; aux < fin; ++aux) {
        total += *aux;
    }
    
    *(sumas + id) = total;
    
    pthread_exit(NULL);
}


void * suma_paralela_con_bloqueo(void * tid)
{
    int id = (int *) tid;
    
    int total = 0;
    
    int elementos = N / NHILOS;
    
    int * inicio = vector + (id * elementos);
    int * fin;
    
    if (id == NHILOS-1) {
        fin = vector + N;
    }
    else {
        fin = inicio + elementos;
    }
    
    for (int * aux = inicio; aux < fin; ++aux) {
        total += *aux;
    }
    
    pthread_mutex_lock(&mutex);
    suma_global += total;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main(int argc, const char * argv[]) {
    
    /* Leer argumentos */
    if (argc == 3) {
        N = atoi(argv[1]);
        NHILOS = atoi(argv[2]);
    }
        
    /* Reservar memoria para el vector */
    vector = (int *) malloc(sizeof(int) * N);
    
    /* Inicializar el vector */
    int * fin = vector + N;
    for (int * aux = vector; aux < fin; ++aux) {
        *aux = 1;
    }
    
    /* Reservar memoria para el vector */
    sumas = (int *) malloc(sizeof(int) * NHILOS);
    
    /* Crear los hilos de ejecución */
    
    /* Variables para medir el tiempo con precisión */
    struct timeval tval_before, tval_after, tval_result;
    
    // Tiempo inicio región paralela
    gettimeofday(&tval_before, NULL);

    pthread_t * hilos = (pthread_t * ) malloc(sizeof(pthread_t) * NHILOS);
    
    for (int i = 0; i < NHILOS; ++i) {
        pthread_create(hilos+i, NULL, suma_paralela, (int *) i);
    }
    
    /* Esperar a que terminen los hilos de ejecución */
    for (int i = 0; i < NHILOS; ++i) {
        pthread_join(*(hilos+i), NULL);
    }
    
    /* Realizar la reducción */
    int total = 0;
    
    fin = sumas + NHILOS;
    for (int * aux = sumas; aux < fin; ++aux) {
        total += *aux;
    }
    
    // Tiempo final región paralela
    gettimeofday(&tval_after, NULL);
    
    timersub(&tval_after, &tval_before, &tval_result);

    
    /* Obtener la suma */
    printf("La suma total paralela es = %d y demoró %ld.%06ld microsegundos\n", total, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec );
    
    /* Obtener la suma */
    
    gettimeofday(&tval_before, NULL);
    
    total = suma();
    
    gettimeofday(&tval_after, NULL);
    
    timersub(&tval_after, &tval_before, &tval_result);

    
    printf("La suma total secuencial es = %d y demoró %ld.%06ld microsegundos\n", total, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec );
    
    /* Liberar la memoria */
    free(vector);
    free(sumas);
    free(hilos);
    
    return 0;
}
