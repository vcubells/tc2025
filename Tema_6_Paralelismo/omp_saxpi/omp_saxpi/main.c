//
//  main.c
//  omp_saxpi
//
//  Created by Vicente Cubells on 02/11/20.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main ()
{
    srand(time(NULL));

    int n = 1 << 30; /* 1M */
    
    float a = 2.0;

    /* Reservar memoria para los vectores */
    float * x = (float *) malloc(sizeof(float) * n);
    float * y = (float *) malloc(sizeof(float) * n);
    float * s = (float *) malloc(sizeof(float) * n);

    #pragma omp parallel shared(x,y,s,n,a)
    {
        /* Inicializar los vectores */
        #pragma omp for
        for (int i = 0; i < n; i++)
        {
            x[i] = (rand() % 10) * 1.0;
            y[i] = (rand() % 10) * 1.0;
        }

        /* SAXPY S = a * X + Y */
        #pragma omp for simd simdlen(4)
        for (int i = 0; i < n; i++)
        {
            s[i] = a * x[i] + y[i];
        }
    }

    /* Visualizar el top 10 */
    for (int i = 0; i < 10; i++)
    {
        printf("%5.2f = %5.2f * %5.2f + %5.2f\n", \
            s[i], a, x[i], y[i]);
    }

    /* Liberar memoria de los vectores */
    free(x);
    free(y);
    free(s);

    return 0;
}
