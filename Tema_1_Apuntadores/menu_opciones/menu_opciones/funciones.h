//
//  funciones.h
//  menu_opciones
//
//  Created by Vicente Cubells on 18/02/21.
//  Copyright © 2021 Vicente Cubells Nonell. All rights reserved.
//

#ifndef funciones_h
#define funciones_h

void abrir(int);
void guardar(int);
void salir(int);
void copiar(int);
void cortar(int);
void pegar(int);

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

void cortar(int opcion)
{
    printf("%d - Cortando el texto...\n", opcion);
}

void pegar(int opcion)
{
    printf("%d - Pegando el texto...\n", opcion);
}

#endif /* funciones_h */
