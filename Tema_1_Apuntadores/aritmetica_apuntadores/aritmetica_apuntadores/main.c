//
//  main.c
//  aritmetica_apuntadores
//
//  Created by Vicente Cubells on 13/08/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void imprime_tradicional(int *, int);
void imprime_combinado(int *, int);
void imprime_aritmetica(int *, int *);

int main(int argc, const char * argv[]) {
   
    /* 1.--- Crear un arreglo dinámicamente --- */
    
    /* Leer el número de elementos */
    int n = 0;
    
    printf("Entra la cantidad de elementos: ");
    scanf("%d", &n);
    
    /* Reservar memoria */
    int * numeros = (int *) malloc(n * sizeof(int)); // malloc, realloc, calloc <-> new / delete
    
    /* Establecer la semmilla del generador de números aleatorios */
    srand((int) time(NULL));
    
    /* Obtener la dirección del último elemento */
    int * fin = numeros + n;
    
    /* Generar números aleatorios */
    for (int * aux = numeros; aux < fin; ++aux) { /* ¿Por qué no hacer numeros++ ? */
        *aux = rand() % 100;
    }
    
    
    /* 2.--- Imprimir los elemento del arreglo --- */
    
    /* Tradicional solo índices */
    imprime_tradicional(numeros, n);
    
    /* Combinación de índices y AA */
    imprime_combinado(numeros, n);
    
    /* Aritmética de apuntadores */
    imprime_aritmetica(numeros, fin);
    
    
    /* 3.--- Reservando más memoria --- */
    
    /* Leer el número de elementos nuevos */
    int m = 0;
    
    printf("Entra la cantidad de elementos nuevos: ");
    scanf("%d", &m);
    
    /* Redimensionar la memoria */
    numeros = (int *) realloc(numeros, (n + m) * sizeof(int));
    
    /* Obtener la dirección del último elemento */
    fin = numeros + n + m;
    
    /* Generar números aleatorios para nuevos elementos*/
    for (int * aux = numeros + n; aux < fin; ++aux) {
        *aux = rand() % 100;
    }
    

    /* 4.--- Imprimir los elemento del arreglo --- */
    
    /* Aritmética de apuntadores */
    imprime_aritmetica(numeros, fin);
    
    
    /* 5.--- Liberar memoria --- */
    free(numeros);
    
    return 0;
}


/* Tradicional solo índices */
void imprime_tradicional(int * numeros, int n)
{
    printf("-- Tradicional ---\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t", numeros[i]);
    }
    printf("\n");
}

/* Combinación de índices y AA */
void imprime_combinado(int * numeros, int n)
{
    printf("-- Combinada ---\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t", *(numeros+i)); // numeros[i] = *(numeros+i)
    }
    printf("\n");
}

/* Aritmética de apuntadores */
void imprime_aritmetica(int * inicio, int * fin)
{
    printf("-- Aritmética de apuntadores ---\n");
    for (int * aux = inicio; aux < fin; ++aux) {
        printf("%d\t", *aux);
    }
    
    printf("\n");
}

