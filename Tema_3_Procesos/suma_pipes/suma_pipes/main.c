//
//  main.c
//  suma_pipes
//
//  Created by Vicente Cubells on 10/09/21.
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void leer(int * fd);
void escribir(int * fd);

int main(int argc, const char * argv[])
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
    int c = -1;
    
    int suma = 0;
    
    while( c != 0 )
    {
        close(fd[1]);
        read(fd[0], &c, sizeof(int));
        
        printf("---  Recibí un %d \n", c);
        
        suma += c;
        
    }
    
    printf("La suma acumulada es: %d \n", suma);
}

void escribir(int * fd)
{
    int num = -1;
    
    while( num != 0)
    {
        printf("Entre un número: ");
        scanf("%d", &num);
        close (fd[0]);
        printf("+++ Envío %d \n", num);
        write(fd[1], &num, sizeof(int));
        sleep(1);
    }
    
    
}



