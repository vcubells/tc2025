//
//  main.c
//  omp_parallel_basico
//
//  Created by Vicente Cubells on 02/11/20.
//

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>

void inicializa(double * vector, long int n)
{
    double * fin = vector + n;
    for (double * aux = vector; aux < fin; ++aux) {
        *aux = (double) rand() / RAND_MAX;
    }
}

double suma(double * vector, long int n, int nhilos)
{
    int i;
    double suma = 0.;
    
    #pragma omp parallel private(i) shared(vector, n, suma)  num_threads(nhilos) if (n > 1000)
    {
        /* Obtener el thread id */
        //tid = omp_get_thread_num();
        
        //nthreads = omp_get_num_threads();
        
        
//        /* Particionar los datos */
//        int elementos = N / nthreads;
//
//        int inicio = tid * elementos;
//        int fin;
//
//        if (tid == nthreads-1) {
//            fin = N;
//        }
//        else {
//            fin = inicio + elementos;
//        }
        
        /* Paralelizar la suma */
        #pragma omp for reduction(+:suma)
        for (i = 0; i < n; ++i) {
            suma += *(vector + i);
        }
        
//        printf("Soy el hilo = %d y mi suma es = %d\n", tid, suma_global);
        
        /* Solo el master lo ejecuta */
        //if (tid == 0)
//        #pragma omp master
//        {
//            printf("%d hilos obtuvieron la suma = %d\n", nthreads, suma_global);
//        }
    

    } /* Join automático */
    
    return suma;
    
}

char * get_schedule_kind(omp_sched_t kind)
{
    switch (kind) {
        case omp_sched_static:
            return "STATIC";
            break;
        case omp_sched_dynamic:
            return "DYNAMIC";
            break;
        case omp_sched_guided:
            return "GUIDED";
            break;
        case omp_sched_auto:
            return "AUTO";
            break;
    }
    
    return "";
}

int main(int argc, const char * argv[]) {
    
    int NHILOS = 12;
    
    long int N = 10;
    
    double suma_global = 0.;
    
    /* Leer argumentos */
    if (argc > 1) {
        N = atoi(argv[1]);
    }
   
    if (argc > 2) {
        NHILOS = atoi(argv[2]);
    }
     
    /* Reservar memoria para el vector */
    double * vector = (double *) malloc(sizeof(double) * N);
    
    /* Inicializar el vector */
    inicializa(vector, N);
    
    //omp_set_schedule(omp_sched_static, 100);
    
    double t_inicio = omp_get_wtime();
    
    suma_global = suma(vector, N, NHILOS);
    
    double t_fin = omp_get_wtime();
    
    double tiempo = t_fin-t_inicio;
    
    double Mflops = (N / tiempo) * 1e-6;
    
    /* Obtener la distribución */
    omp_sched_t kind;
    int chunk_size;
    omp_get_schedule(&kind, &chunk_size);
    
    printf("La suma total es = %.4lf, de %ld elementos, demoró %.6lf segundos, con %d hilos, en %.6lf Mflops y %.6lf Mflops por hilo, usando distribución '%s' con chunksize = %d\n", suma_global, N, tiempo, NHILOS, Mflops, Mflops / NHILOS, get_schedule_kind(kind), chunk_size );
    
    
    free(vector);
    
    return 0;
}
