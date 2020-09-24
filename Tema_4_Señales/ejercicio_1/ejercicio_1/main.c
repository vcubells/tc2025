//
//  main.c
//  ejercicio_1
//
//  Created by Vicente Cubells on 24/09/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, const char * argv[])
{
    pid_t pid;
    
    signal(SIGTSTP, SIG_IGN);
    
    pid = fork();
    
    if (pid == 0)
    {
        signal(SIGINT, SIG_IGN);
        
        printf("Soy el hijo con PID %d, mi padre es %d y me voy a dormir 2 segundos\n", getpid(), getppid());
        
        sleep(2);
        
        printf("Soy el hijo con PID %d, mi padre es %d y acabo de despertar. Contaré hasta 10\n", getpid(), getppid());
        
        int i = 1;
        
        while(i <= 10) {
            printf("Hijo contando hasta ... %d\n", i++);
            sleep(1);
        }
        
        printf("Soy el hijo con PID %d, mi padre es %d y voy a terminar\n", getpid(), getppid());
        
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Soy el PADRE con PID %d y si pulsas Ctrl + C solo terminaré yo. Me voy a dormir 10 segundos\n", getpid());
        
        sleep(10);
        
        printf("Soy el PADRE y acabo de despertar. Esperaré a que termine mi hijo con PID %d.\n", pid);
        
        waitpid(pid, NULL, 0);
        
        printf("Soy el PADRE y ya me voy. Adiós...\n");
    
    }
    
    return 0;
}
