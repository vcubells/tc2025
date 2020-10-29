//
//  main.c
//  problema_baño_mujeres_hombres
//
//  Created by Vicente Cubells on 21/10/20.
//

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

// Definir el número de hilos, uno por cada proceso distinto, 4 en total
#define NHILOS 4

// Definir semáforos a utilizar para sincronización en la entrada y salida del sanitario
// No puede salir un hombre o mujer si no ha entrado alguno con anterioridad
sem_t sem_hombres_adentro;
sem_t sem_mujeres_adentro;

// Variable que define el estado del sanitario
// 0 = vacío; 1 = ocupado por mujeres; 2 = ocupado por hombres
int estado_sanitario = 0;

// Definir e inicializar el mutex que protege la variable compartida "estado_sanitario"
pthread_mutex_t mutex_estado_sanitario = PTHREAD_MUTEX_INITIALIZER;


// Prototipo de las funciones
void * hombre_quiere_entrar(void *);
void * hombre_sale(void *);
void * mujer_quiere_entrar(void *);
void * mujer_sale(void *);


// Programa principal
int main(int argc, char **argv)
{
    pthread_t hilos[NHILOS];
    int result, i;
    
    //Inicializar los semáforos de sincronización
    sem_init(&sem_hombres_adentro, 0, 0);
    sem_init(&sem_mujeres_adentro, 0, 0);
    
    // Crear los hilos para cada función (4 en total)
    result = pthread_create(&hilos[0], NULL, hombre_quiere_entrar, NULL);
    if (result)
        printf("Error al crear 'hombre_quiere_entrar' \n");
    
    result = pthread_create(&hilos[1], NULL, mujer_quiere_entrar, NULL);
    if (result)
        printf("Error al crear 'mujer_quiere_entrar' \n");
    
    result = pthread_create(&hilos[2], NULL, hombre_sale, NULL);
    if (result)
        printf("Error al crear 'hombre_sale' \n");
    
    result = pthread_create(&hilos[3], NULL, mujer_sale, NULL);
    if (result)
        printf("Error al crear 'mujer_sale' \n");
        
    // Esperar que terminen los hilos
    for(i = 0; i < NHILOS; ++i)
    {
        result = pthread_join(hilos[i], NULL);
        if (result)
            printf("Error al adjuntar el hilo %d \n", i);
    }
    
    //Liberar memoria ocupada por semáforos
    sem_destroy(&sem_hombres_adentro);
    sem_destroy(&sem_mujeres_adentro);
    
    //Garantizar que se liberen los recursos de los hilos
    pthread_exit(NULL);
    
}

void * hombre_quiere_entrar(void * arg)
{
    int hombres_en_espera = 0;
    
    while (1)
    {
        sleep(rand() % 5);
        
        printf("Llega un hombre. En espera hay %d \n", ++hombres_en_espera );            // Se incrementa la cantidad de hombres en espera
        
        pthread_mutex_lock(&mutex_estado_sanitario);                                    // Protege el acceso a la variable global compartida "estado_sanitario"

        if (!estado_sanitario)                                                            // Verifica si el sanitario está vacío, si es así, hombre puede entrar
        {
            estado_sanitario = 2;                                                        // Se actualiza el estado del sanitario a ocupado por hombres
            
            printf("El sanitario está ocupado por hombres \n");
        }
        
        if (estado_sanitario == 2)                                                        // Verificar si está ocupado por hombres
        {
            printf("Entra un hombre. En espera quedan %d \n", --hombres_en_espera);        // Se decrementa la cantidad de hombres en espera
                        
            sem_post(&sem_hombres_adentro);                                                // Se incrementa la cantidad de hombres adentro
        }
        
        pthread_mutex_unlock(&mutex_estado_sanitario);                                    // Se libera el acceso a la variable compartida "estado_sanitario"
        
    }
    
    pthread_exit(NULL);
}

void * hombre_sale(void * arg)
{
    int hombres_adentro = 0;
    
    while (1)
    {
        
        sem_wait(&sem_hombres_adentro);                                                    // Si no hay hombre adentro, no puede salir
        
        sem_getvalue(&sem_hombres_adentro, &hombres_adentro);                            // Se obtiene la cantidad de hombres adentro
        
        printf("Sale un hombre. Quedan adentro %d hombres \n", hombres_adentro);
        
        if (!hombres_adentro)                                                            // Si no quedan hombres adentro, el sanitario está vacío
        {
            pthread_mutex_lock(&mutex_estado_sanitario);                                // Se protege el acceso a la variable compartida "estado_sanitario"
            
            estado_sanitario = 0;                                                        // Se actualiza el estado del sanitario a vacío
            
            printf("El sanitario está vacío \n");
            
            pthread_mutex_unlock(&mutex_estado_sanitario);                                // Se libera el acceso a la variable compartida "estado_sanitario"
        }
    }
    
    pthread_exit(NULL);
}


void * mujer_quiere_entrar(void * arg)
{
    int mujeres_en_espera = 0;
    
    while (1)
    {
        sleep(rand() % 5);
        
        printf("Llega una mujer. En espera hay %d \n", ++mujeres_en_espera );            // Se incrementa la cantidad de mujeres en espera
        
        pthread_mutex_lock(&mutex_estado_sanitario);                                    // Protege el acceso a la variable global compartida "estado_sanitario"

        if (!estado_sanitario)                                                            // Verifica si el sanitario está vacío, si es así, mujer puede entrar
        {
            estado_sanitario = 1;                                                        // Se actualiza el estado del sanitario a ocupado por mujeres
            
            printf("El sanitario está ocupado por mujeres \n");
        }
        
        if (estado_sanitario == 1)                                                        // Verificar si está ocupado por mujeres
        {
            printf("Entra una mujer. En espera quedan %d \n", --mujeres_en_espera);        // Se decrementa la cantidad de mujeres en espera
            
            sem_post(&sem_mujeres_adentro);                                                // Se incrementa la cantidad de mujeres adentro
        }
        
        pthread_mutex_unlock(&mutex_estado_sanitario);                                    // Se libera el acceso a la variable compartida "estado_sanitario"
        
    }
    
    pthread_exit(NULL);
}

void * mujer_sale(void * arg)
{
    int mujeres_adentro = 0;
    
    while (1)
    {
            
        sem_wait(&sem_mujeres_adentro);                                                    // Si no hay mujer adentro, no puede salir
                
        sem_getvalue(&sem_mujeres_adentro, &mujeres_adentro);                            // Se obtiene la cantidad de mujeres adentro
        
        printf("Sale una mujer. Quedan adentro %d mujeres \n", mujeres_adentro);
        
        if (!mujeres_adentro)                                                            // Si no quedan mujeres adentro, el sanitario está vacío
        {
            sleep(rand()%5);
            pthread_mutex_lock(&mutex_estado_sanitario);                                // Se protege el acceso a la variable compartida "estado_sanitario"
            
            estado_sanitario = 0;                                                        // Se actualiza el estado del sanitario a vacío
            
            printf("El sanitario está vacío \n");
            
            pthread_mutex_unlock(&mutex_estado_sanitario);                                // Se libera el acceso a la variable compartida "estado_sanitario"
        }
    }
    
    pthread_exit(NULL);
}
