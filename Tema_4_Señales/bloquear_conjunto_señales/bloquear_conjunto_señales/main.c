//
//  main.c
//  bloquear_conjunto_señales
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

void gestor(int sid)
{
    printf("Procesando el Ctrl+C\n");
}

int main(int argc, const char * argv[])
{
    sigset_t conjunto, pendientes;
    int i;
    
    sigemptyset(&conjunto);
    
    sigaddset(&conjunto, SIGINT);
    
    sigaddset(&conjunto, SIGTSTP);
    
    sigprocmask(SIG_BLOCK, &conjunto, NULL);
    
    signal(SIGINT, gestor);
    
    for( i= 0; i < 10; ++i)
    {
        printf("Las señales SIGINT y SIGTSTP están bloqueadas ... \n");
        sleep(1);
        sigpending(&pendientes);
        
        if (sigismember(&pendientes, SIGINT))
            printf("He recibido un Ctrl+C y no lo procesé por estar bloqueada. \n");
        if (sigismember(&pendientes, SIGTSTP))
            printf("He recibido un Ctrl+Z y no lo procesé por estar bloqueada. \n");
        
    }
    
    sigprocmask(SIG_UNBLOCK, &conjunto, NULL);
    
    printf("Se desbloquearon las señales y se procesaron");
    
    while(1);
    
    return 0;
}
