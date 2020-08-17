//
//  main.c
//  longitud_cadena
//
//  Created by Vicente Cubells Nonell on 17/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

long int longitudAA(char *);
long int longitudContador(char *);
long int longitudCombinado(char * );

int main(int argc, const char * argv[]) {
    char * cadena;
    int longitud;
    
    printf("Dame la longitud máxima: ");
    scanf("%d", &longitud);
    
    cadena = (char *) malloc(sizeof(char) * longitud);
    
    printf("Entre una cadena: ");
    scanf(" %[^\n]", cadena);
    //scanf("%s", cadena);
    //fgets()
    
    // Obtener longitud de una cadena con contador
    
    printf("La longitud con Contador es %ld \n", longitudContador(cadena));
    
    //Obtener longitud con AA
    
    printf("La longitud con AA es %ld \n", longitudAA(cadena) );
    
    //Obtener longitud Combinado
    
    printf("La longitud Combinado es %ld \n", longitudCombinado(cadena) );
    
    free(cadena);
    
    return 0;
}

long int longitudAA( char * cadena)
{
    char * p = cadena;
    while (*p++ != '\0'){};
    
    return (p - cadena - 1);
}

long int longitudContador(char * cadena)
{
    int c = 0;
    char * p = cadena;
    while (*p++ != '\0')
        //++p;
        ++c;
    
    return c;
}

long int longitudCombinado(char * cadena)
{
    int c = 0;
    while (*(cadena+c) != '\0')
        ++c;
    
    return c;
}

/*
 
 cadena
 |
 queremos ir a la playa\0
                        |
                        p
 p - cadena - 1
 
 */
