//
//  main.c
//  factorial_sockets
//
//  Created by Vicente Cubells Nonell on 28/09/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define TCP_PORT 8000

unsigned long long int factorial (int num);

/* reverse:  reverse string s in place */
void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(unsigned long long int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}



int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int servidor, cliente;
    
    int leidos, escritos;
    
    /* Leer la IP donde va a escuchar el servidor */
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    /* Crear el socket */
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    /* Crear la struct con los datos */
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    /* Establecer enlace entre IP y Puerto */
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    /* Abrir el socker en modo escucha con máximo 10 clientes */
    listen(servidor, 10);
    
    /* Obtener tamaño de la struct */
    socklen_t tamano = sizeof(direccion);
    
    /* Aceptar conexiones de los clientes */
    cliente = accept(servidor, (struct sockaddr *) &direccion, &tamano);
    
    unsigned long long int fact;
    
    if (cliente >= 0) {
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        /* Leer del socket */
        while (leidos = read(cliente, &buffer, sizeof(buffer))) {
            
            /* Convertir a int */
            int numero = atoi(buffer);
            
            /* Mostrar por pantalla el número recibido */
            printf("Número recibido: %d\n", numero);
            
            /* Calcular el factorial */
            fact = factorial(numero);
            
            /* Convertir el factorial a un string */
            itoa(fact, buffer);
            
            /* Mostrar por pantalla el factorial */
            printf("Factorial de %d : %s\n", numero, buffer);
            
            /* Escribir en el socket */
            write(cliente, buffer, sizeof(buffer));
        }
    }
    
    /* Cerrar el socket del servidor */
    close(servidor);
    
    /* Cerrar el socket del cliente */
    close(cliente);
    
    return 0;
}

unsigned long long int factorial (int num)
{
    unsigned long long int f = 1;
    int i;
    for(i = 2; i <= num; ++i)
        f *= i;
    
    return f;
}

