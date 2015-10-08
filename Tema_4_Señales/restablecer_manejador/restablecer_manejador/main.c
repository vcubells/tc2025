//
//  main.c
//  restablecer_manejador
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <signal.h>
#include <stdio.h>

void gestor_ctrlc (int);

int main(int argc, const char * argv[])
{
    int k =10;
    
    struct sigaction gestor, gestor_viejo;
    
    if (argc<2) {
        printf("Uso correcto: # %s [I|D|M] \n", argv[0]);
        printf("\t\t( I=Ignorar	D=Defecto	M=Manejador programado )\n");
        exit(-1);
    }
    
    switch ( toupper(argv[1][0]) ) {
        case 'I' : gestor.sa_handler = SIG_IGN ; break;
        case 'D' : gestor.sa_handler = SIG_DFL ; break;
        case 'M' : gestor.sa_handler = gestor_ctrlc; break;
        default :
            printf("Opción no válida. Debe ser I, D o M .\n");
            exit(-1);
    }
    
    gestor.sa_flags = SA_RESTART;
    
    if (sigaction(SIGINT, &gestor, 0) == -1 )
    {
        printf("Error en el gestor de señales.\n");
        exit(-1);
    }
    
    /* Leer el gestor */
    sigaction(SIGINT, 0, &gestor_viejo);
    if (gestor_viejo.sa_handler == SIG_DFL) printf("Tenías el valor predetermminado\n");
    else if (gestor_viejo.sa_handler == SIG_IGN) printf("La señal SIGINT se está ignorando\n");
    
    while (1)
    {
        printf("Antes del pause()\n");
        pause();
        printf("Después del pause()\n");
    }
    
}

void gestor_ctrlc (int senial)
{
    printf("***** Ha pulsado CTRL + C (señal número %d) \n", senial);
}