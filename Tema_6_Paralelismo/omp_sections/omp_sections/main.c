//
//  main.c
//  omp_sections
//
//  Created by Vicente Cubells on 09/11/20.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    long int i;
    
    long int N = 1000;
    
    /* Leer argumentos */
    if (argc > 1) {
        N = atoi(argv[1]);
    }

    /* Reservar memoria para los vectores */

    double * a = (double *) malloc(sizeof(double) * N);
    double * b = (double *) malloc(sizeof(double) * N);
    double * c = (double *) malloc(sizeof(double) * N);
    double * d = (double *) malloc(sizeof(double) * N);
    
    /* Inicialización */
    for (i=0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
    }
    
    double t_inicio = omp_get_wtime();

    #pragma omp parallel shared(a,b,c,d) private(i)
    {
        #pragma omp sections nowait
        {
            #pragma omp section
            for (i=0; i < N; i++)
                c[i] = a[i] + b[i];
            #pragma omp section
            for (i=0; i < N; i++)
                d[i] = a[i] * b[i];
        }  /* fin secciones */
    }  /* fin paralela */
    
    double tiempo = omp_get_wtime() - t_inicio;
    
    printf("Demoró con dos secciones %.6lf segundos...\n", tiempo );
    
    t_inicio = omp_get_wtime();

    #pragma omp parallel for shared(a,b,c,d) private(i) num_threads(6)
            for (i=0; i < N; i++)
                c[i] = a[i] + b[i];
       
    #pragma omp parallel for shared(a,b,c,d) private(i) num_threads(6)
            for (i=0; i < N; i++)
                d[i] = a[i] * b[i];

    
    tiempo = omp_get_wtime() - t_inicio;
    
    printf("Demoró con dos for %.6lf segundos...\n", tiempo );

    t_inicio = omp_get_wtime();

    #pragma omp parallel for shared(a,b,c,d) private(i) num_threads(6)
        for (i=0; i < N; i++) {
                c[i] = a[i] + b[i];
                d[i] = a[i] * b[i];
        }

    tiempo = omp_get_wtime() - t_inicio;

    printf("Demoró con un for %.6lf segundos...\n", tiempo );

    /* Liberar memoria de los vectores */
    free(a);
    free(b);
    free(c);
    free(d);

    return 0;

}
