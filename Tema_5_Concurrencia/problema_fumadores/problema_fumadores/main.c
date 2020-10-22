//
//  main.c
//  problema_fumadores
//
//  Created by Vicente Cubells on 21/10/20.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define ITERACIONES 20

int tabaco = 0;
int cerillas = 0;
int papel = 0;

int consumidos = 0;

pthread_mutex_t ingr_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t agente = PTHREAD_COND_INITIALIZER;
pthread_cond_t fumadores = PTHREAD_COND_INITIALIZER;

void * agente_productor(void * );
void * fumador_tabaco_cerillas(void * );
void * fumador_papel_cerillas(void * );
void * fumador_tabaco_papel(void * );

int main(int argc, const char * argv[])
{
    pthread_t agenteP, fumadorTC, fumadorPC, fumadorTP;
    
    srand((int) time(NULL));
    
    /* Crear el hilo agente */
    pthread_create(&agenteP, NULL, agente_productor, NULL);
    
    /* Crear el hilo fumador 1 */
    pthread_create(&fumadorTC, NULL, fumador_tabaco_cerillas, NULL);
    
    /* Crear el hilo fumador 2 */
    pthread_create(&fumadorPC, NULL, fumador_papel_cerillas, NULL);
    
    /* Crear el hilo fumador 3 */
    pthread_create(&fumadorTP, NULL, fumador_tabaco_papel, NULL);

    /* Esperar a que los hilos terminen */
    pthread_join(agenteP, NULL);
    pthread_join(fumadorTC, NULL);
    pthread_join(fumadorPC, NULL);
    pthread_join(fumadorTP, NULL);
    
    pthread_exit(NULL);
}


void * agente_productor(void * param) {
    int i, j;
    
    int count = 0;
    
    while (count < ITERACIONES) {
        
        pthread_mutex_lock(&ingr_mutex);
        
        if ( (tabaco || cerillas || papel) && (count < ITERACIONES) ) {
            pthread_cond_wait(&agente, &ingr_mutex);
        }
        else {
            
            i = rand() % 3;
            j = i;
            
            while (j == i) {
                j = rand() % 3;
            }
            
            tabaco = (i == 0) || (j == 0);
            cerillas = (i == 1) || (j == 1);
            papel = (i == 2) || (j == 2);
            
            if (tabaco && cerillas) {
                printf("(A-%d) El agente produce tabaco y cerillas\n", count);
            }
            else if (tabaco && papel) {
                printf("(A-%d) El agente produce tabaco y papel\n", count);
            }
            else {
                printf("(A-%d) El agente produce papel y cerillas\n", count);
            }
            
            ++count;
            
            pthread_cond_broadcast(&fumadores);
            }
        
        pthread_mutex_unlock(&ingr_mutex);
    };
    
    printf("(A) El agente termina \n");
    
    pthread_exit(NULL);
};

void * fumador_tabaco_cerillas(void * param) {
    while (consumidos < ITERACIONES) {
        
        pthread_mutex_lock(&ingr_mutex);
        
        if (tabaco && cerillas) {
            
            printf("(TC-%d) El fumador con tabaco y cerillas está fumando\n", consumidos);
            
            tabaco = 0;
            cerillas = 0;
            
            ++consumidos;
            
            pthread_cond_signal(&agente);
        }
        else if (consumidos < ITERACIONES) {
            
            pthread_cond_wait(&fumadores, &ingr_mutex);
        }
        
        pthread_mutex_unlock(&ingr_mutex);
    }
    
    printf("(TC) El fumador con tabaco y cerillas termina\n");
        
    pthread_exit(NULL);
}

void * fumador_papel_cerillas(void * param) {
    while (consumidos < ITERACIONES) {
        
        pthread_mutex_lock(&ingr_mutex);
        
        if (papel && cerillas) {
            
            printf("(PC-%d) El fumador con papel y cerillas está fumando\n", consumidos);
            
            papel = 0;
            cerillas = 0;
            
            ++consumidos;
            
            pthread_cond_signal(&agente);
        }
        else if (consumidos < ITERACIONES) {
            pthread_cond_wait(&fumadores, &ingr_mutex);
        }
        
        pthread_mutex_unlock(&ingr_mutex);
    }
    
    printf("(PC) El fumador con papel y cerillas termina\n");
        
    pthread_exit(NULL);
}

void * fumador_tabaco_papel(void * param) {
    while (consumidos < ITERACIONES) {
        
        pthread_mutex_lock(&ingr_mutex);
        
        if (tabaco && papel) {
            
            printf("(TP-%d) El fumador con tabaco y papel está fumando\n", consumidos);
            
            tabaco = 0;
            papel = 0;
            
            ++consumidos;
            
            pthread_cond_signal(&agente);
        }
        else if (consumidos < ITERACIONES) {
            pthread_cond_wait(&fumadores, &ingr_mutex);
        }
        
        pthread_mutex_unlock(&ingr_mutex);
    }
    
    printf("(TP) El fumador con tabaco y papel termina\n");
        
    pthread_exit(NULL);
}

