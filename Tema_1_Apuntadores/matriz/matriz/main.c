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

int main(int argc, const char * argv[]) {
    
    int N;
    int M;
    
    printf("Dame el número de filas: ");
    scanf("%d", &N);
    
    printf("Dame el número de columnas: ");
    scanf("%d", &M);
    
    int * matriz = (int *) malloc(sizeof(int) * N * M);
    
    leeMatriz(matriz, N, M);
    imprimeMatriz(matriz, N, M);
    
    
    free(matriz);
    
    return 0;
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