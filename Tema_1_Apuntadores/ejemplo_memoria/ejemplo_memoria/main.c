//
//  main.c
//  ejemplo_memoria
//
//  Created by Vicente Cubells on 10/08/21.
//

#include <stdio.h>
#include <stdlib.h>

/* Variable global que utiliza almacenamiento estático */
int global;

int main(int argc, const char * argv[]) {
    
    /* Variable estática explícitamente */
    static int estatica;
    
    /* Variable automática */
    int automatica = 0;
    
    printf("Global = %d\n", global);
    printf("Estática = %d\n", estatica);
    
    printf("Automática = %d\n", automatica);
    
    int n = 1;
    printf("Entre la longitud de tu arreglo:");
    scanf("%d", &n);
    
    /* Memoria dinámica */
    int * arreglo = (int *) malloc(n * sizeof(int));
    
    /* Usar el arreglo */
    
    /* Liberar explícitamente la memoria dinámica */
    free(arreglo);
    
    return 0;
}
