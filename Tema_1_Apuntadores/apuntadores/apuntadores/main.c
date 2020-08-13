//
//  main.c
//  apuntadores
//
//  Created by Vicente Cubells Nonell on 14/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 60

/*
 operador de dirección & -> Regresa una dirección de memoria
 operador de indirección * -> Obtiene el contenido de una dirección de memoria
 
            #FFFF
 
 ptr_n ->   #FF00   - n - 50
 
            #00FF
 
            #0000  -  ptr_n - #FF00
 */


void imprime(int * , int *);

int main(int argc, const char * argv[]) {
    int n = 50;
    
    int * ptr_n = &n;
    
    void * ptr_g;           // Apuntador genérico
    
    ptr_g = ptr_n;          // Apunta a un int
    
    float flot = 4.5;
    
    float * ptr_f = &flot;  // Apunta a un float
    
    ptr_g = ptr_f;
    
    ptr_g = &flot;          // Apunta a un float
    
    ptr_g = &n;             // Apunta a un int
    
    ptr_g = &ptr_n;
    

    /* Leer el número de elementos */
    printf("Entra la cantidad de elementos: ");
    scanf("%d", &n);
    
    /* Reservar memoria */
    int * numeros = (int *) malloc(n * sizeof(int));
    
    /* Generar números aleatorios */
    srand((int) time(NULL));
    
    int * aux;
    int * fin = numeros + n;
    for (aux = numeros; aux < fin; ++aux) {
        *aux = rand() % 100;
    }
    
    /* Imprimir los números */
    
    imprime(numeros, fin);
    
    /* Reservando mas memoria */
    
    int m = 0;
    
    /* Leer el número de elementos nuevos */
    printf("Entra la cantidad de elementos nuevos: ");
    scanf("%d", &m);
    
    /* Redimensionar la memoria */
    
    numeros = (int *) realloc(numeros, (n + m) * sizeof(int));
    
    /* Generar números aleatorios para nuevos elementos*/
    srand((int) time(NULL));
    
    fin = numeros + n + m;
    
    for (aux = numeros + n; aux < fin; ++aux) {
        *aux = rand() % 100;
    }
    
    /* Imprimir los números */
    
    imprime(numeros, fin);
    
    /* Liberar memoria */
    
    free(numeros);
    
    return 0;
}

void imprime(int * inicio, int * fin)
{
    int * aux;
    
    for (aux = inicio; aux < fin; ++aux) {
        printf("%d\t", *aux);
    }
    
    printf("\n");
}


