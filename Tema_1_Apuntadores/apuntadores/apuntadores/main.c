//
//  main.c
//  apuntadores
//
//  Created by Vicente Cubells Nonell on 14/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>

#define N 60

/*
 operador de dirección & -> Regresa una dirección de memoria
 operador de indirección * -> Obtiene el contenido de una dirección de memoria
 
            #FFFF
 
 ptr_n ->   #FF00   - n - 50
 
            #00FF
 
            #0000  -  ptr_n - #FF00
 */

int main(int argc, const char * argv[]) {
    
    /* Apuntadores a enteros */
    
    int n = 50;
    
    int * ptr_n = &n;
    
    void * ptr_g;           // Apuntador genérico
    
    ptr_g = ptr_n;          // Apunta a un int
    
    printf("Dirección de n = %p\n", ptr_n);
    printf("Dirección de ptr_g =  %p \n", ptr_g);
    printf("Contenido de n = %d\n", n);
    printf("Contenido de ptr_g = %d\n",*((int *)ptr_g));
    printf("Contenido de ptr_n = %d\n",*ptr_n);
    
    /* Apuntadores a flotantes */
    
    float flot = 4.5;
    
    float * ptr_f = &flot;  // Apunta a un float
    
    ptr_g = ptr_f;
    
    ptr_g = &flot;          // Apunta a un float
    
    printf("Dirección de flot = %p\n", ptr_f);
    printf("Dirección de ptr_g =  %p \n", ptr_g);
    printf("Contenido de float = %f\n", flot);
    printf("Contenido de ptr_g = %f\n",*((float *)ptr_g));
    printf("Contenido de ptr_f = %f\n",*ptr_f);
    
    ptr_g = &n;             // Apunta a un int
    
    printf("Dirección de ptr_g =  %p \n", ptr_g);
    
    ptr_g = &ptr_n;

    printf("Dirección de ptr_g =  %p \n", ptr_g);

    return 0;
}
