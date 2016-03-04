//
//  main.c
//  pipe
//
//  Created by Vicente Cubells Nonell on 07/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>

void leer(int fd);
void escribir(int fd);

int main(int argc, const char * argv[])
{
    int tuberia[2];
    pid_t pid;
    
    pipe(tuberia);
    
    pid = fork();
    
    if (pid == -1)
    {
        printf("Error al crear el proceso hijo");
        exit(-1);
    }
    else if (pid == 0)
    {
        /* Hijo */
        close(tuberia[1]);
        
        printf(" Soy el hijo y estoy leyendo ... \n");
        
        leer(tuberia[0]);
    }
    else {
        /* Padre */
        
        close(tuberia[0]);
        
        printf(" Soy el padre y estoy escribiendo ... \n");
        
        escribir(tuberia[1]);
    }
    
    return 0;
}

void leer(int fd)
{
    FILE * file;
    int c;
    
    file = fdopen(fd, "r");
    
    while ( (c = fgetc(file)) != EOF )
    {
        printf("<<<<<< ------ Leyendo del PIPE : ");
        putchar(c);
        printf("\n");
    }
    
    fclose(file);
}

void escribir(int fd)
{
    FILE * file;
    file = fdopen(fd, "w");
    
    sleep(10);
    
    int n = 0;
    while (n++ < 10) {
        printf(" ---->>>> Soy el padre y estoy escribiendo\n");
        fprintf(file, "%d", n);
    }
    
    fclose(file);
}
