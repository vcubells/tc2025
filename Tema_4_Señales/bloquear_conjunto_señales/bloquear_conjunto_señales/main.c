//
//  main.c
//  bloquear_conjunto_señales
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

int main(int argc, const char * argv[])
{
    sigset_t conjunto, pendientes;
    int i;
    
    sigemptyset(&conjunto);
    
    sigaddset(&conjunto, SIGINT);
    
    sigprocmask(SIG_BLOCK, &conjunto, NULL);
    
    for( i= 0; i < 10; ++i)
    {
        printf("La señal SIGINT está bloqueada ... \n");
        sleep(1);
        sigpending(&pendientes);
        
        if (sigismember(&pendientes, SIGINT))
            printf("He recibido un Ctrl+C y no lo procesé por estar bloqueada. \n");
        
    }
    
    sigprocmask(SIG_UNBLOCK, &conjunto, NULL);
    printf("Ya se desbloqueó la señal");
    
    while(1);
    
    return 0;
}
