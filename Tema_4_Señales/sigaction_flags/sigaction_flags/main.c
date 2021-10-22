//
//  main.c
//  sigaction_flags
//
//  Created by Vicente Cubells Nonell on 08/10/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TIEMPO 10

int bucle = 1;
int numcortes = 0;

void gestor_alarma (int senial)
{
    bucle = 0;
    printf("Se acabo!\n");
}

void gestor_ctrlc(int senial)
{
    int res = alarm(TIEMPO);
    printf("Pulso CTRL + C, te quedaban %d seg\n", res);
    ++numcortes;
    
}

int main(int argc, const char * argv[])
{
    struct sigaction gestion;
    int err;
    
    gestion.sa_handler = gestor_ctrlc;
    gestion.sa_flags = SA_RESTART;
    
    err = sigaction (SIGINT, &gestion, 0);
    
    if (err==-1)
    {
        perror("SIGINT\n");
        exit(-1);
    }
    
    gestion.sa_handler = gestor_alarma;
    gestion.sa_flags = SA_RESETHAND;
    
    err = sigaction (SIGALRM, &gestion, 0);
    
    if (err==-1)
    {
        perror("SIGALARM\n");
        exit(-1);
    }
    
    printf("Pulse varias veces CTRL + C durante %d segundos.\n", TIEMPO);
    
    alarm(TIEMPO);
    
    while (bucle);
    
    gestion.sa_handler = SIG_IGN;
    gestion.sa_flags = SA_RESETHAND;
    
    err = sigaction (SIGINT, &gestion, 0);
    
    if (err==-1)
    { 
        perror("SIGINT\n"); 
        exit(-1); 
    } 
    
    printf("Has intentado cortar %d veces.\n", numcortes);
    
    //while(1);
    
    exit(0); 
}
