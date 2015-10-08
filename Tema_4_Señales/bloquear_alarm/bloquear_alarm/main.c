//
//  main.c
//  bloquear_alarm
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>

void gestor(int s)
{
    printf("Mi alarma se generó hace 10 seg pero estaba bloqueada. Ya pasaron 20 seg.");
}

int main(int argc, const char * argv[])
{
    sigset_t conjunto;
    
    sigemptyset(&conjunto);
    
    sigaddset(&conjunto, SIGALRM);
    
    sigprocmask(SIG_BLOCK, &conjunto, NULL);
    
    signal(SIGALRM, gestor);
    
    alarm(10);
    
    sleep(20);
    
    sigprocmask(SIG_UNBLOCK, &conjunto, NULL);
    
    while(1);
    
    
    return 0;
}
