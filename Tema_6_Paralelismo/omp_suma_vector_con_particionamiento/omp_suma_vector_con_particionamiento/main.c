//
//  main.c
//  omp_suma_vector_con_particionamiento
//
//  Created by Vicente Cubells on 02/11/20.
//

#include <omp.h>
#include <stdio.h>

#define ELEMENTOS 1000

int main()
{
    int nthreads, tid;
    double t_inicial, t_final;

    int vector[ELEMENTOS];
    int total = 0;
    
    //omp_set_num_threads(8);

    /* Inicializar el vector */
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < ELEMENTOS; i++)
    {
        vector[i] = 1;
        printf("Hilo %d, elemento %d\n", \
        omp_get_thread_num(), i );
    }
    
    t_inicial = omp_get_wtime();
    /* Cada hilo tienen una variable tid privada */
    #pragma omp parallel private(tid) if (ELEMENTOS > 100)  //num_threads(4)
    {
        /* Obtener el thread id */
        tid = omp_get_thread_num();
        
        /* Obtener número de hilos */
        int nhilos = omp_get_num_threads();

        /* Particionamiento de los datos */
        int slots = ELEMENTOS / nhilos;
        int inicio = tid * slots;
        int fin;
        if (tid == nhilos - 1)
        {
            fin = ELEMENTOS;
        }
        else {
            fin = inicio + slots;
        }

        /* Sumar elementos */
        int suma_local = 0;
        for (int i = inicio; i < fin; i++)
        {
            suma_local += 1;
        }

        /* Región crítica */
        #pragma omp critical
        {
            total += suma_local;
        }
          
        printf("Hilo %d, Inicio = %d, Fin = %d, Suma = %d\n", \
            tid, inicio, fin, suma_local                           \
        );
    }
    t_final = omp_get_wtime();

    printf("El total es %d, calculada en %.8f\n", total, t_final-t_inicial);

    return 0;
}
