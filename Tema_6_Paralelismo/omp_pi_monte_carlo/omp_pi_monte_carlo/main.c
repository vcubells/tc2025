//
//  main.c
//  omp_pi_monte_carlo
//
//  Created by Vicente Cubells on 20/05/21.
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    long n = 1 << 30; // 1M
    
    double m = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:m)
    for (int i = 0; i < n; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        
        double d = x * x + y * y;
        
        if( d <= 1) {
            ++m;
        }
    }

    double pi = m/n*4 ;
    double delta = omp_get_wtime() - start;

    printf("PI = %.16g calculado en %.4g segundos con %ld puntos\n", pi, delta, n);
}
