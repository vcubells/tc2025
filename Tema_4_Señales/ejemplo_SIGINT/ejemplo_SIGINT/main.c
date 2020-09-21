//
//  main.c
//  ejemplo_SIGINT
//
//  Created by Vicente Cubells Nonell on 01/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

void manejador(int ids)
{
    if (ids == 2) {
        printf("--- Recibí la señal %d Ctrl + C ...\n", ids);
    }
    else {
        printf("--- Recibí la señal %d ...\n", ids);
    }
}

int main(int argc, const char * argv[]) {
    
    if (signal(SIGINT, manejador) == SIG_ERR) {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    
    if (signal(SIGTSTP, manejador) == SIG_ERR) {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    
    // A partir de aquí Ctrl+C no termina el programa
    
    int k = 10;
    
    while (k-- > 0) {
        printf(" +++ %d y contando\n", k);
        sleep(5);
    }
    
    return 0;
}
