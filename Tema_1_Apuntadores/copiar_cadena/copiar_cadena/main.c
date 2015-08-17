//
//  main.c
//  copiar_cadena
//
//  Created by Vicente Cubells Nonell on 17/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * copiar(char *);

int main(int argc, const char * argv[])
{
    
    char * cadena;
    int longitud;
    
    printf("Dame la longitud máxima: ");
    scanf("%d", &longitud);
    
    cadena = (char *) malloc(sizeof(char) * longitud);
    
    printf("Entre una cadena: ");
    scanf("%s", cadena);
    
    
    //Copiar una cadena a otra;
	   
    char * destino = copiar(cadena);
    
    printf("Cadena origen = %s \n", cadena );
    printf("Cadena destino = %s \n", destino );
    
    free(cadena);
    free(destino);
}

char * copiar(char * cadena)
{
    long int c = strlen(cadena);
    
    char * destino = (char *) malloc(sizeof(char) * c);
    
    char * p = cadena;
    char * d = destino;
    
    while ( (*d++ = *p++) != '\0') {};
    
    return destino;
    
}

