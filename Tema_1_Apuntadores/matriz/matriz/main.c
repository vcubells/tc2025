//
//  main.c
//  matriz
//
//  Created by Vicente Cubells Nonell on 14/01/16.
//  Copyright © 2016 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


void leeMatriz(int * m, int filas, int columnas);

void imprimeMatriz(int * m, int filas, int columnas);

int get_item(int * matriz, int fila, int columna, int numero_columnas);

int main(int argc, const char * argv[]) {
    
    int N;
    int M;
    
    printf("Dame el número de filas: ");
    scanf("%d", &N);
    
    printf("Dame el número de columnas: ");
    scanf("%d", &M);
    
    int * matriz = (int *) malloc(sizeof(int) * N * M);
    
    //int * matriz = (int *) calloc(N * M, sizeof(int));
    
    leeMatriz(matriz, N, M);
    imprimeMatriz(matriz, N, M);
    
    int f = 1;
    int c = 1;
    
    printf("m[1][1] = %d\n", get_item(matriz, f, c, M) );
    
    free(matriz);
    
    return 0;
}

/*
   C++ vector<int> v(iniciales = 5, incr = 3); -> malloc(5*sizeof(int))
   Java Vector<int> v;
   C# List<int> v;
 
   v.insert() 1 2 3 4 5, 6 -> realloc (iniciales + incr), 7, 8, 9 -> realloc (iniciales + incr)
   v.push()
   v.push_back()
    
 */


int get_item(int * matriz, int fila, int columna, int numero_columnas)
{
    return *(matriz + (fila * numero_columnas) + columna);
}

void imprime_tradicional(int * m, int filas, int columnas)
{
    /* Obtener la posición de un elemento
     item[i][j] = m + (i * columnas) + j
     */
    
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
          //  printf("[%d, %d] = %d ", i, j, m[i][j]);
        }
        printf("\n");
    }
}


void leeMatriz(int * m, int filas, int columnas)
{
    int f = 0;
    int c = 0;
    int * temp = m;
    int * final = m + (filas * columnas);
    
    for (; temp < final; ++temp) {
        printf(" [ %d, %d ] = ", f, c++);
        scanf("%d", temp);
        if (c % columnas == 0) {
            c = 0;
            ++f;
        }
    }
}

void imprimeMatriz(int * m, int filas, int columnas)
{
    int f = 0;
    int c = 0;
    int * temp = m;
    int * final = m + (filas * columnas);
    
    for (; temp < final; ++temp) {
        printf("%5d", *temp);
        c++;
        if (c % columnas == 0) {
            c = 0;
            ++f;
            printf("\n");
        }

    }
}
