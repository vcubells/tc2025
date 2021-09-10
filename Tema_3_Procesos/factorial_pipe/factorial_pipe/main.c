//
//  main.c
//  factorial_pipe
//
//  Created by Vicente Cubells Nonell on 10/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void leer(int * fd);
void escribir(int * fd);
unsigned long int factorial (int num);

int main(int argc, char **argv)
{
    
    pid_t pid;
    int tubo[2];
    
    /* Crear un pipe */
    pipe(tubo); // 0- significa que no hay error
    
    pid = fork();
    
    if (pid == 0)
    {
        /* Estoy en el hijo */
        printf("Estoy leyendo y soy el hijo ... \n");
        leer(tubo);
        printf("Soy el proceso hijo y voy a terminar\n");
    }
    else if (pid == -1)
    {
        /* Error al crear el proceso hijo */
        exit(-1);
    }
    else {
        /* Estoy en el padre */
        printf("Estoy escribiendo y soy el padre ... \n");
        escribir(tubo);
        printf("Soy el proceso padre y espero que termine el hijo\n");
        wait(NULL);
    }
    
    
    return 0;
}

void leer(int * fd)
{
    int c = 0;
    
    while( c != -1 )
    {
        close(fd[1]);
        read(fd[0], &c, sizeof(int));
        if (c != -1) {
            printf("---  Recibí f(%d) = %lu  \n", c, factorial(c));
        }
    }
}

void escribir(int * fd)
{
    int num = 0;
    
    
    while( num != -1)
    {
        printf("Entre un número: ");
        scanf("%d", &num);
        close (fd[0]);
        printf("+++ Envío %d \n", num);
        write(fd[1], &num, sizeof(int));
        sleep(1);
    }
    
    
}

unsigned long int factorial (int num)
{
    unsigned long int f = 1;
    int i;
    for(i = 2; i <= num; ++i)
        f *= i;
    
    return f;
}



