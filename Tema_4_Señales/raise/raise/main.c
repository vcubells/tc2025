//
//  main.c
//  raise
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>


void gestor(int senial)
{
    printf("***** Mi papá me mandó un SIGUSR1 y lo voy a matarrrrrrrrrr\n", senial);
    kill(getppid(), SIGKILL);
    printf("y ahora por remordimiento me voy a suicidar ....\n");
    raise(SIGKILL);
}

int main(int argc, const char * argv[])
{
    pid_t pid;
    
    pid = fork();
    
    if (pid == 0)
    {
        signal(SIGUSR1, gestor);
        printf("Soy el hijo y sigo vivo\n");
        while(1);
    }
    else if (pid > 0)
    {
        sleep(3);
        printf("Soy el PADRE y voy a comunicarme con mi hijo con PID = %d\n", pid);
        kill(pid, SIGUSR1);
        printf("Dormiré feliz......\n");
        while(1);
        
    }
    
    return 0;
}
