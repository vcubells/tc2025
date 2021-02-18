//
//  main.c
//  ordenamiento
//
//  Created by Vicente Cubells Nonell on 20/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void ordena(int *, int (*)(int, int));
int asc(int, int);
int desc(int, int);

int main(int argc, const char * argv[]) {
   
    int * valores = (int *) malloc(N * sizeof(int));
    
    int * p = valores;
    
    srand((int) time(NULL));
    
    for (; p < (valores + N); ++p) {
        *p = rand() % 100;
        printf("%4d", *p);
    }
    
    ordena(valores, asc);
    
    
    printf("\n\n--- Ordenados ---\n\n");
    
    for (p = valores; p < (valores + N); ++p) {
        printf("%4d", *p);
    }
    
    free(valores);
    
    return 0;
}

void ordena(int * numeros, int criterio(int, int))
{
    int i, j, temp;
    
    for(i = 0; i < N; ++i)
    {
        for(j = N-1; j > i; --j)
        {
            //if (numeros[j] < numeros[j-1])
            if (criterio(numeros[j],numeros[j-1])) {
                temp = numeros[j-1];
                numeros[j-1] = numeros[j];
                numeros[j] = temp;
            }
        }
    }
}

int asc(int a, int b)
{
    return a < b;
}

int desc(int a, int b)
{
    return b < a;
}
