//
//  main.c
//  omp_factorial
//
//  Created by Vicente Cubells on 02/11/20.
//

#include <omp.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    int n = 5;
    long int factorial = 1;

    double start = omp_get_wtime();

    #pragma omp parallel for shared(n) reduction(*:factorial)
    for (int i = 2; i <= n; i++)
    {
        factorial *= i;
    }

    double delta = omp_get_wtime() - start;

    printf("%d! = %d calculado en %.4g segundos \n", n, factorial, delta);
}
