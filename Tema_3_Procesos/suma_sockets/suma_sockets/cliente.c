//
//  cliente.c
//  suma_sockets
//
//  Created by Vicente Cubells on 17/09/21.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[])
{
    struct sockaddr_in direccion;
    char buffer[1000];
    
    int cliente;
    
    ssize_t leidos, escritos;
    
    if (argc != 2) {
        printf("Use: %s IP_Servidor \n", argv[0]);
        exit(-1);
    }
    
    // Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);
    
    // Establecer conexión
    inet_aton(argv[1], &direccion.sin_addr);
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    
    escritos = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));
    
    if (escritos == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        // Leer números e ir acumulando la suma
        int suma  = 0;
        int numero = -1;
        
        while (numero != 0) {
            printf("Entre un número: ");
            scanf("%d\n", &numero);
            
            suma += numero;
        }
        
        /* Convertir suma en in char * y transmitir el char* */
        // Escribir datos en el socket
        write(cliente, suma, sizeof(int));
    }
    
    // Cerrar sockets
    close(cliente);
    
    return 0;
}

