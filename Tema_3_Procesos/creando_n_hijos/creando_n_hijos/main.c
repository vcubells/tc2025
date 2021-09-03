//
//  main.c
//  creando_n_hijos
//
//  Created by Vicente Cubells on 31/08/21.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 5

int main(int argc, const char * argv[]) {
    
    pid_t * pids = (pid_t *) malloc(N * sizeof(pid_t));
    pid_t * end = pids + N;
    
    for(pid_t * aux = pids; aux < end; ++aux)
    {
        *aux = fork();
        
        if (*aux == -1) {
            printf("Error creando el proceso\n");
        }
        else if (*aux == 0) {
            printf("Se creó un hijo con PID = %d y padre = %d \n", getpid(), getppid());
            //sleep(rand() % 300);
            exit(0);
        }
    }
    
    for(pid_t * aux = pids; aux < end; ++aux)
    {
        //waitpid(*aux, NULL, 0);
        wait(NULL);
    }
    
    free(pids);
    
    return 0;
}
