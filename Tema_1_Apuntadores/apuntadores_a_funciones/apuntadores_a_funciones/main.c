//
//  main.c
//  apuntadores_a_funciones
//
//  Created by Vicente Cubells Nonell on 18/01/16.
//  Copyright © 2016 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define N 4

typedef void (* menu_t)();

void opcion1();
void opcion2();
void opcion3();
void opcion4();

int main(int argc, const char * argv[]) {
   
    int opcion = -1;
    
    menu_t * opciones = (menu_t *) malloc(N * sizeof(menu_t));
    
    *opciones = opcion1;
    *(opciones+1) = opcion2;
    *(opciones+2) = opcion3;
    *(opciones+3) = opcion4;
    
    while (opcion != 0) {
        printf("1-Opción 1\n2-Opción 2\n3-Opción 3\n4-Opción 4\n0-Salir\n");
        
        printf("Selecciona tu opción: ");
        scanf("%d", &opcion);
        
        if (opcion > 0 && opcion <= N) {
            (*(opciones[opcion-1]))();
        }
        
        
//        switch (opcion) {
//            case 1:
//                opcion1();
//                break;
//            case 2:
//                opcion2();
//                break;
//            case 3:
//                opcion3();
//                break;
//                
//            default:
//                break;
//        }
    }
    
    free(opciones);
    
    return 0;
}

void opcion1()
{
    printf("Seleccionaste la opción 1\n");
}

void opcion2()
{
    printf("Seleccionaste la opción 2\n");
}

void opcion3()
{
    printf("Seleccionaste la opción 3\n");
}

void opcion4()
{
    printf("Seleccionaste la opción 4\n");
}

