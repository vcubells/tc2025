//
//  main.c
//  conjunto_señales
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

int main(int argc, const char * argv[])
{
    
    sigset_t ninguna, todas;
    
    sigemptyset(&ninguna);
    sigfillset(&todas);
    
    //sigaddset(&ninguna, SIGINT);
    
    
    if (sigismember(&ninguna, SIGINT))
        printf("SIGINT pertenece al conjunto ninguna\n");
    else
        printf("SIGINT no pertenece al conjunto ninguna \n");
    
    //sigdelset(&todas, SIGINT);
    
    if (sigismember(&todas, SIGINT))
        printf("SIGINT pertenece al conjunto todas \n");
    else
        printf("SIGINT no pertenece al conjunto todas \n");
    
    return 0;
}
