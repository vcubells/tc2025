#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    // Posicion 0 es pos de lectura y 1 es de escritura
    int tuberia1[2];
    int tuberia2[2];
    pid_t pid;

    // Crea el pipe
    pipe(tuberia1);
    pipe(tuberia2);

    // Hacer fork, los dos prcesos tienen conocimiento de la estructura
    pid = fork();

    if(pid == -1)
    {
        printf("Error al crear al proceso hijo\n");
        exit(-1);
    }
    else if(pid == 0)
    {
        int factorial, numero, bits, i;

        while(1)
        {
            // Cerrar escritura antes de leer, no cerrar lectura despues de leer
            close(tuberia1[1]);
            bits = read(tuberia1[0], &numero, sizeof(int));
            if(bits == sizeof(int))
            {
                if(numero == 0) exit(0);

                factorial = 1;
                for(i = 1; i <= numero; ++i)
                {
                    factorial *= i;
                }
                close(tuberia2[0]);
                write(tuberia2[1], &factorial, sizeof(int));
            }
        }
    }
    else
    {
        int num = 1;
        int fact;
        while(num  != 0)
        {
            scanf("%d", &num);
            // Cerrar lectura antes de escribir, no cerrar ecritura despues...
            close(tuberia1[0]);
            write(tuberia1[1], &num, sizeof(int));

            close(tuberia2[1]);
            read(tuberia2[0], &fact, sizeof(int));
            if(num != 0)
            {
                printf("El factorial es %d\n", fact);
            }
        }
    }
    return 0;
}
