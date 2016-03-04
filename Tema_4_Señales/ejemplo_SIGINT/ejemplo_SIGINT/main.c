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
    printf("--- Oprimiste Ctrl+C ...\n");
}

int main(int argc, const char * argv[]) {
    
    if (signal(SIGKILL, manejador) == SIG_ERR) {
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
