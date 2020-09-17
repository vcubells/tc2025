//
//  cliente.c
//  factorial_sockets
//
//  Created by Vicente Cubells Nonell on 28/09/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[]) {
    
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int cliente;
    
    int leidos, escritos;
    
    /* Leer la IP del servidor */
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    /* Crear el socket */
    cliente = socket(PF_INET, SOCK_STREAM, 0);
    
    /* Establecer los campos de la struct */
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    /* Establecer la conexión con el servidor */
    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    /*  Comunicación entre cliente-servidor */
    if (estado == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        /* Lee el número entrado por teclado */
        while (leidos = read(fileno(stdin), &buffer, sizeof(buffer))) {
            /* Escribir el número en el socket */
            write(cliente, &buffer, leidos);
            
            /* Espera y lee resultado del servidor */
            leidos = read(cliente, &buffer, sizeof(buffer));
            
            /* Imprime el valor obtenido en el socket */
            printf("Factorial = %s\n", buffer);
        }
    }
    
    /* Cerrar el socket */
    close(cliente);
    
    return 0;
}



