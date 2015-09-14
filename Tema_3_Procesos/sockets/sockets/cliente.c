//
//  cliente.c
//  sockets
//
//  Created by Vicente Cubells Nonell on 14/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
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
    
    if (argc != 2) {
        printf("Error. Use: %s A.B.C.D \n", argv[0]);
        exit(-1);
    }
    
    //Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);
    
    // Establecer conexión
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    inet_aton(argv[1], &direccion.sin_addr);
    
    int estado = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Comunicación
    
    if (estado == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer de teclado y escribir en socket
        while (leidos = read(fileno(stdin), &buffer, sizeof(buffer))) {
            write(cliente, &buffer, leidos);
            
            leidos = read(cliente, &buffer, sizeof(buffer));
            write(fileno(stdout), &buffer, leidos);
        }
    }
    
    // Cerrar el socket
    close(cliente);
    
    return 0;
}


