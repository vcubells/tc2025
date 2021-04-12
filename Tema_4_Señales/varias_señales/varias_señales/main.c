//
//  main.c
//  varias_señales
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void gestor_ctrlc (int);
void gestor_ctrlz (int);

int main(int argc, const char * argv[])
{
    int i,j,k =10;
    
    void (*ret_signal_z)();
    void (*ret_signal_c)();
        
    printf("******************************************************\n");
    printf("******** Terminará al pulsar 3 veces CTRL + Z *******\n");
    printf("******************************************************\n\n");
    
    ret_signal_z = signal(SIGTSTP, gestor_ctrlz ) ;
    ret_signal_c = signal(SIGINT, gestor_ctrlc ) ;
    
    if (ret_signal_z == SIG_ERR || ret_signal_c == SIG_ERR )
    {
        printf("Error en el gestor de señales.\n");
        exit(-1);
    }
    
    while(k-- > 0)
    {
        printf("(%d) PID=%d. Esperando CTRL + C o CTRL + Z\n", k, getpid() );
        sleep(2);
    }
}

void gestor_ctrlc (int senial) {
    printf("***** Ha pulsado CTRL + C (señal numero %d) \n", senial);
}

void gestor_ctrlz (int senial) {
    static int cont=0;
    
    printf("***** Ha pulsado CTRL + Z (señal numero %d) \n", senial);
    
    if (cont++ == 2)
        exit(-1);
}
