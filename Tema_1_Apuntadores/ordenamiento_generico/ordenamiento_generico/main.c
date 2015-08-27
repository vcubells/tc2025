//
//  main.c
//  ordenamiento_generico
//
//  Created by Vicente Cubells Nonell on 27/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

#define N 20

/* Tipos de funciones */

typedef int (*t_compare)(void *, void *);

typedef void (*t_swap)(void * , void * );

typedef void (*t_sort)(void *, size_t, size_t, t_compare, t_swap );

/* Funciones genéricas */

void sort(t_sort, void *, size_t , size_t, t_compare, t_swap );

void insertionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap );
void selectionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap );

/* Funciones callback para enteros */

int ascInt(void * , void * );
int descInt(void * , void * );

void swapInt(void * , void * );

/* Funciones callback para flotantes */

int ascFloat(void * , void * );
int descFloat(void * , void * );

void swapFloat(void * , void * );

/* Funciones de impresión */

void imprimeInt(int *, int );

void imprimeFloat(float *, int );


int main(int argc, const char * argv[])
{
    
    /* Ordenar números enteros */
    
    int * vector = (int *) malloc(N * sizeof(int));
    
    int * aux = vector;
    int * last = vector + N;
    
    for (; aux < last; ++aux) {
        *aux = rand() % 100;
    }
    
    printf("\n\n--- Enteros ---\n\n");
    
    imprimeInt(vector, N);
    
    sort(&selectionSort, vector, N, sizeof(*vector), &ascInt, &swapInt);
    
    printf("\n\n--- Enteros Ordenados ---\n\n");
    
    imprimeInt(vector, N);
    
    free(vector);
    
    /* Ordenar números flotantes */
    
    float * vectorf = (float *) malloc(N * sizeof(float));
    
    
    float * auxf = vectorf;
    float * lastf = vectorf + N;
    
    for (; auxf < lastf; ++auxf) {
        *auxf = rand() % 100 * 1.5;
    }
    
    printf("\n\n--- Flotantes ---\n\n");
    
    imprimeFloat(vectorf, N);
    
    sort(&insertionSort, vectorf, N, sizeof(*vectorf), &descFloat, &swapFloat);
    
    printf("\n\n--- Flotantes Ordenados ---\n\n");
    
    imprimeFloat(vectorf, N);
    
    free(vectorf);
    
    return 0;
}

/* Implementación de funciones genéricas */

void sort(t_sort algorithm, void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    (*algorithm)(vector, count, size, compare, swap);
}

void insertionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    void * j;
    void * start = vector;
    void * aux = start;
    void * last = start + (count * size);
    
    for (; aux < last ; aux+=size)
    {
        j = aux - size;
        while (j >= start && (*compare)(j, j+size) )
        {
            (*swap)(j+size, j);
            j-=size;
        }
    }
}

void selectionSort(void * vector, size_t count, size_t size, t_compare compare, t_swap swap )
{
    void * minimo;
    
    void * j;
    void * start = vector;
    void * aux = start;
    void * last = start + (count * size);
    void * prelast = last - size;
    
    for(; aux < prelast; aux+=size)
    {
        minimo = aux;
        for(j = aux + size; j < last; j+=size)
        {
            if ( (*compare)(minimo, j) )
                minimo = j;
        }
        
        (*swap)(minimo, aux);
    }
}

/* Implementación de funciones callback para enteros */

int ascInt(void * pa, void * pb)
{
    int * a = (int *)pa;
    int * b = (int *)pb;
    return (*a > *b);
}

int descInt(void * pa, void * pb)
{
    int * a = (int *)pa;
    int * b = (int *)pb;
    return (*a < *b);
}

void swapInt(void * pa , void * pb )
{
    int temp;
    int * a = (int *)pa;
    int * b = (int *)pb;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
}


/* Implementación de funciones callback para flotantes */

int ascFloat(void * pa, void * pb)
{
    float * a = (float *)pa;
    float * b = (float *)pb;
    return (*a > *b);
}

int descFloat(void * pa, void * pb)
{
    float * a = (float *)pa;
    float * b = (float *)pb;
    return (*a < *b);
}

void swapFloat(void * pa , void * pb )
{
    float temp;
    float * a = (float *)pa;
    float * b = (float *)pb;
    
    temp = *a;
    *a = *b;
    *b = temp;
    
}

/* Implementación de funciones de impresión */

void imprimeInt(int * vector, int count)
{
    int * aux = vector;
    int * last = vector + count;
    
    for (; aux < last; ++aux) {
        printf(" %4d ", *aux);
    }
    
    printf("\n");
}

void imprimeFloat(float * vector, int count)
{
    float * aux = vector;
    float * last = vector + count;
    
    for (; aux < last; ++aux) {
        printf(" %7.2f ", *aux);
    }
    
    printf("\n");
}

