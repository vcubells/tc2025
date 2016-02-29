#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    // Posicion 0 es pos de lectura y 1 es de escritura
    int tuberia[2];
    pid_t pid;

    // Crea el pipe
    pipe(tuberia);

    // Hacer fork, los dos prcesos tienen conocimiento de la estructura
    pid = fork();

    if(pid == -1)
    {
        printf("Error al crear al proceso hijo\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        int suma, numero, bits;
        suma = 0;
        while(1)
        {
            // Cerrar escritura antes de leer, no cerrar lectura despues de leer
            close(tuberia[1]);
            bits = read(tuberia[0], &numero, sizeof(int));
            if(bits == sizeof(int))
            {
                if(numero != 0)
                {
                    suma += numero;
                }
                else
                {
                    printf("La suma es %d\n", suma);
                    exit(0);
                }
            }
        }
    }
    else
    {
        int num = 1;
        while(num  != 0)
        {
            scanf("%d", &num);
            // Cerrar lectura antes de escribir, no cerrar ecritura despues...
            close(tuberia[0]);
            write(tuberia[1], &num, sizeof(int));
        }
    }
    return 0;
}
