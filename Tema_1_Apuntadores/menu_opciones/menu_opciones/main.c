//
//  main.c
//  menu_opciones
//
//  Created by Vicente Cubells Nonell on 20/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef void (*opcion_t) (int);

void abrir(int);
void guardar(int);
void salir(int);
void copiar(int);

int main(int argc, const char * argv[]) {
    
    opcion_t * menu = (opcion_t *) malloc( N * sizeof(opcion_t));
    
    *menu = abrir;
    *(menu+1) = guardar;
    *(menu+2) = salir;
    *(menu+3) = copiar;
    
    
    printf("--- Opciones --- \n1-Abrir\n2-Guardar\n3-Salir\n4-Copiar\nEscoge tu opción: ");
    
    int opcion;
    
    scanf("%d", &opcion);
    
    /* Utilizando switch */
    
//    switch (opcion) {
//        case 1:
//            abrir(opcion);
//            break;
//
//        case 2:
//            guardar(opcion);
//            break;
//
//        case 3:
//            salir(opcion);
//            break;
//
//        case 4:
//            copiar(opcion);
//            break;
//
//        default:
//            printf("Opción no válida\n");
//            break;
//    }
    
    /* Apuntadores a funciones */
    /* nombre(opcion) */
    (*(menu+opcion-1))(opcion);
    // menu[opcion-1](opcion);
    
    free(menu);
    
    return 0;
}

void abrir(int opcion)
{
    printf("%d - Abriendo el archivo...\n", opcion);
}

void guardar(int opcion)
{
    printf("%d - Guardando el archivo...\n", opcion);
}

void salir(int opcion)
{
    printf("%d - Terminando el programa...\n", opcion);
}

void copiar(int opcion)
{
    printf("%d - Copiando el archivo...\n", opcion);
}

