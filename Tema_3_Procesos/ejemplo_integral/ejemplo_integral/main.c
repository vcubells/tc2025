//
//  main.c
//  ejemplo_integral
//
//  Created by Vicente Cubells Nonell on 04/02/16.
//  Copyright © 2016 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 1000000

int suma(int *, int, int);
void print(int *, int, int);

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    int estado;
    
    srand(time(NULL));
    
    int * numeros = (int *) malloc(N * sizeof(int));
    
    /* Inicializar valores */
    
    int * temp = numeros;
    int * last = numeros + N;
    for (; temp < last; ++temp) {
        *temp = rand() % 2;
        //printf("%3d ", *temp);
    }
    
    printf("\n");
    
    /* Crear el primer proceso hijo */
    pid = fork();
    
    /* De aquí en adelante lo ejecutan los dos procesos */
    if (pid == -1)
    {
        printf("Error al crear el proceso hijo 1\n");
    }
    else if (pid == 0)
    {
        // Estamos en el hijo
        
        printf("--- Valores en el Hijo 1 ---- \n");
        //print(numeros, 0, N/2);
        int resultado = suma(numeros, 0, N/2);
        printf("Hijo 1 con PID %d, Suma  = %d \n", \
               getpid(), resultado);
        
        free(numeros);
        
        exit(resultado);
    }
    else {
        // Estamos en el padre
        printf("Estamos en el proceso padre con PID = %d \n", \
               getpid());
        
        /* Crear el segundo proceso hijo */
        pid_t pid2 = fork();
        
        /* De aquí en adelante lo ejecutan los dos procesos */
        if (pid2 == -1)
        {
            printf("Error al crear el proceso hijo 2\n");
        }
        else if (pid2 == 0)
        {
            // Estamos en el hijo
            printf("--- Valores en el Hijo 2 ---- \n");
            //print(numeros, N/2, N);
            
            int resultado = suma(numeros, N/2, N);
            printf("Hijo 2 con PID %d, Suma  = %d \n", \
                   getpid(), resultado);
            
            free(numeros);
            
            exit(resultado);
        }
        else {
            
            int total = 0;
            
            // Poner al padre a esperar que el hijo 1 termine
            if (waitpid(pid, &estado, 0) != -1)
            {
                if (WIFEXITED(estado)) {
                    printf("Ya terminó el hijo 1 con PID %d con suma = %d \n", pid, WEXITSTATUS(estado));
                    
                    total += WEXITSTATUS(estado);
                }
            }
            
            // Poner al padre a esperar que el hijo 2 termine
            if (waitpid(pid2, &estado, 0) != -1)
            {
                if (WIFEXITED(estado)) {
                    printf("Ya terminó el hijo 2 con PID %d con suma = %d \n", pid2, WEXITSTATUS(estado));
                    
                    total += WEXITSTATUS(estado);
                }
            }
            
            printf("La suma total es = %d \n", total);
            
            free(numeros);
            
        }

        
    }
    
    return 0;
}

int suma(int * numeros, int inicio, int fin)
{
    int * temp = numeros + inicio;
    int * final = numeros + fin;
    
    int total = 0;
    
    for (; temp < final; ++temp) {
        total += *temp;
    }
    
    return total;
}

void print(int * numeros, int inicio, int fin)
{
    int * temp = numeros + inicio;
    int * final = numeros + fin;
    
    for (; temp < final; ++temp) {
        printf("%3d ", *temp);
    }
    
    printf("\n");
}



