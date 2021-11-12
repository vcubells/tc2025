//
//  main.c
//  omp_parallel
//
//  Created by Vicente Cubells Nonell on 05/11/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <omp.h>

#define N 1000003

int main(int argc, const char * argv[]) {
    int i;
    int suma = 0;
    double inicio, fin;
    
    inicio = omp_get_wtime();
    
    //#pragma omp parallel private(i)
    //{
       // int tid = omp_get_thread_num();
        
        #pragma omp parallel for private(i) reduction(+:suma)
        for (i = 0; i < N; ++i) {
            suma += 1;
        }
        
      //  printf("Soy el hilo %d y mi Suma = %d \n", tid, suma);
   // }
    
    fin = omp_get_wtime();
    
    printf("Tiempo  = %f , Suma = %d\n", fin-inicio, suma);
    
    return 0;
}
