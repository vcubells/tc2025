//
//  main.c
//  omp_pi
//
//  Created by Vicente Cubells on 02/11/20.
//

#include <omp.h>
#include <stdio.h>

int main(int argc, const char *argv[])
{
    long n = 1 << 30; // 1M

    double h = 1.0 / (double)n;

    double area = 0.0;
    double x;

    double start = omp_get_wtime();

    #pragma omp parallel for private(x) shared(n,h) reduction(+:area)
    for (int i = 0; i < n; i++)
    {
        x = (i + 0.5) * h;
        area += (4.0 / (1.0 + x * x));
    }

    double pi = h * area;
    double delta = omp_get_wtime() - start;

    printf("PI = %.16g calculado en %.4g segundos con %ld puntos\n", pi, delta, n);
}
