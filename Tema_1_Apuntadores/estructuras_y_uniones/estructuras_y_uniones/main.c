//
//  main.c
//  estructuras_y_uniones
//
//  Created by Vicente Cubells Nonell on 14/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[30];
    char apellidos[30];
    int edad;
} persona;

typedef union {
    char nombre[30];
    char apellidos[30];
    int edad;
} persona_u;


int main(int argc, const char * argv[])
{
    
    persona e;
    persona_u u;
    
    strcpy(e.nombre, "Juan");
    strcpy(e.apellidos, "Perez");
    e.edad = 89;
    
    printf(" Valores en la estructura:\n\n");
    
    printf("%s %s (%d)\n\n", e.nombre, e.apellidos, e.edad);
    
    
    strcpy(u.nombre, "Juan");
    strcpy(u.apellidos, "Perez");
    u.edad = 89;
    
    printf(" Valores en la unión:\n\n");
    
    printf("%s %s (%d)\n\n", u.nombre, u.apellidos, u.edad);
    
    
    return 0;
}

