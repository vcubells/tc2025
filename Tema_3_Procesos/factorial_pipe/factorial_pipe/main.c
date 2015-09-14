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
int factorial (int num);

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
    }
    
    
    return 0;
}

void leer(int * fd)
{
    int c;
    
    while( 1 )
    {
        close(fd[1]);
        read(fd[0], &c, sizeof(int));
        printf("---  Recibí f(%d) = %d  \n", c, factorial(c));
    }
    
}
void escribir(int * fd)
{
    int num;
    
    
    while(1)
    {
        printf("Entre un número: ");
        scanf("%d", &num);
        close (fd[0]);
        printf("+++ Envío %d \n", num);
        write(fd[1], &num, sizeof(int));
    }
    
    
}

int factorial (int num)
{
    int f = 1;
    int i;
    for(i = 2; i <= num; ++i)
        f *= i;
    
    return f;
}



