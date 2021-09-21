//
//  main.c
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
    int suma_total = 0;
    
    int servidor, cliente;
    
    ssize_t leidos, escritos;
    int continuar = 1;
    pid_t pid;
    
    if (argc != 2) {
        printf("Use: %s IP_Servidor \n", argv[0]);
        exit(-1);
    }
    
    // Crear el socket
    servidor = socket(PF_INET, SOCK_STREAM, 0);
    
    // Enlace con el socket
    inet_aton(argv[1], &direccion.sin_addr);
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;
    
    bind(servidor, (struct sockaddr *) &direccion, sizeof(direccion));
    
    // Escuhar
    listen(servidor, 10);
    
    escritos = sizeof(direccion);
    
    // Aceptar conexiones
    while (continuar)
    {
        cliente = accept(servidor, (struct sockaddr *) &direccion, &escritos);
        
        printf("Aceptando conexiones en %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
        
        pid = fork();
        
        if (pid == 0) continuar = 0;
        
    }
    
    if (pid == 0) {
        
        close(servidor);
        
        if (cliente >= 0) {
            
            // Leer datos del socket
            while (leidos = read(cliente, &buffer, sizeof(buffer))) {
                
                suma_total += atoi(buffer);
                
                printf("La suma parcial es: %d\n", suma_total);
            }
        }
        
        close(cliente);
    }
    
    else if (pid > 0)
    {
        while (wait(NULL) != -1);
        
        // Cerrar sockets
        close(servidor);
        
    }
    return 0;
}
