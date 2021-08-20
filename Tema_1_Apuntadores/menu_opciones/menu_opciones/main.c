//
//  main.c
//  menu_opciones
//
//  Created by Vicente Cubells Nonell on 20/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

#define N 7

/*  retorno nombre(argv)
    void (*nombre)(int, int)
    int (*nombre)(float)
    char (*nombre)()
    *
 */

typedef void (*opcion_t) (int);

void menu_f(opcion_t * opciones);

int main(int argc, const char * argv[]) {
    
    /* Declaración del arreglo y reservación de memoria */
    opcion_t * menu = (opcion_t *) malloc( N * sizeof(opcion_t));

    /* Asignaciones de opciones al arreglo */
    *menu = abrir;
    *(menu+1) = guardar;
    *(menu+2) = salir;
    *(menu+3) = copiar;
    *(menu+4) = cortar;
    *(menu+5) = pegar;
    *(menu+6) = nueva;
    
    /* Invocación al menú de opciones */
    menu_f(menu);
    
    /* Liberar memoria */
    free(menu);
    
    return 0;
}


void menu_f(opcion_t * opciones)
{
    int opcion;
    
    do {
        printf("--- Opciones --- \n1-Abrir\n2-Guardar\n3-Salir\n4-Copiar\n5-Cortar\n6-Pegar\n7-Nueva\n0-Terminar\nEscoge tu opción: ");

        scanf("%d", &opcion);
        
        if(opcion > 0 && opcion <= N ) {
            (*(opciones+opcion-1))(opcion);
        }
    }
    while (opcion > 0 && opcion <= N);
}


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
//        case 5:
//            opcion_nueva(opcion);
//            break;

//        default:
//            printf("Opción no válida\n");
//            break;
//    }

/* Apuntadores a funciones */
/* nombre(opcion) */

// menu[opcion-1](opcion);
