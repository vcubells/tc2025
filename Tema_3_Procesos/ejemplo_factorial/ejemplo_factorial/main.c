//
//  main.c
//  ejemplo_factorial
//
//  Created by Vicente Cubells Nonell on 28/01/16.
//  Copyright © 2016 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int factorial(int);

int main(int argc, const char * argv[]) {
    
    pid_t pid;
    int numero = 1;
    
    while (numero != 0) {
        printf("Entre un número: ");
        scanf("%d", &numero);
        
        pid = fork();
        
        if (pid == -1)
        {
            printf("Error al crear el proceso hijo \n");
        }
        else if (pid == 0)
        {
            // Estamos en el hijo
            
            /* Calcular el factorial de número */
            
            printf("%d! = %d\n", numero, factorial(numero));
            
            break;
        }
        else {
            // Estamos en el padre
        
            wait(NULL);
        }
    }
    
    return 0;
}

int factorial(int n)
{
    int f = 2;
    int i = 3;
    
    if (n == 0 || n == 1) {
        return 1;
    }
    
    for (; i <= n; f *= i, ++i);
    
    return f;
}
