//
//  main.c
//  pthread_factorial
//
//  Created by Vicente Cubells on 10/05/21.
//

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int NHILOS = 4;
int N = 20;

/* Vector de factoriales parciales */
long long int * factoriales;

void * factorial_paralela(void * tid)
{
    int id = (int *) tid;
    
    long long int factorial = 1;
    
    int elementos = N / NHILOS;
    
    int inicio = (id * elementos) + 1;
    int fin;
    
    if (id == NHILOS-1) {
        fin = N + 1;
    }
    else {
        fin = inicio + elementos;
    }
    
    for (int i = inicio; i < fin; ++i) {
        factorial *= i;
    }
    
    *(factoriales + id) = factorial;
    
    pthread_exit(NULL);
}

int main(int argc, const char * argv[]) {
    
    /* Leer argumentos */
    if (argc == 3) {
        N = atoi(argv[1]);
        NHILOS = atoi(argv[2]);
    }
    
    /* Reservar memoria para el vector */
    factoriales = (long long int *) malloc(sizeof(long long int) * NHILOS);
    
    /* Crear los hilos de ejecución */
    
    /* Variables para medir el tiempo con precisión */
    struct timeval tval_before, tval_after, tval_result;
    
    // Tiempo inicio región paralela
    gettimeofday(&tval_before, NULL);

    pthread_t * hilos = (pthread_t * ) malloc(sizeof(pthread_t) * NHILOS);
    
    for (int i = 0; i < NHILOS; ++i) {
        pthread_create(hilos+i, NULL, factorial_paralela, (int *) i);
    }
    
    /* Esperar a que terminen los hilos de ejecución */
    for (int i = 0; i < NHILOS; ++i) {
        pthread_join(*(hilos+i), NULL);
    }
    
    /* Realizar la reducción */
    long long int total = 1;
    long long int * fin = factoriales + NHILOS;
    for (long long int * aux = factoriales; aux < fin; ++aux) {
        total *= *aux;
    }
    
    // Tiempo final región paralela
    gettimeofday(&tval_after, NULL);
    
    timersub(&tval_after, &tval_before, &tval_result);

    /* Obtener el factorial */
    printf("El factorial de %d es = %lld y demoró %ld.%06ld microsegundos\n", N, total, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec );
    
    /* Liberar la memoria */
    free(factoriales);
    free(hilos);
    
    return 0;
}
