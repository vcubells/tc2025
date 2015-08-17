//
//  main.c
//  biblioteca
//
//  Created by Vicente Cubells Nonell on 17/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int paginas;
    char * titulo;
    char * autor;
    
} libro;


int main(int argc, const char * argv[])
{
    
    libro * biblioteca;
    libro * aux;
    
    int cantidad = 0;
    
    printf("¿Cuántos libros quieres guardar? : ");
    scanf("%d", &cantidad);
    
    biblioteca = (libro *) malloc(sizeof(libro) * cantidad);
    
    libro * final = biblioteca + cantidad;
    
    for (aux = biblioteca; aux < final; ++aux) {
        
        aux->titulo = (char * ) malloc(sizeof(char) * 25);
        
        printf("Entre el título del libro: ");
        scanf("%s", aux->titulo);
        
        aux->autor = (char * ) malloc(sizeof(char) * 25);
        
        printf("Entre el autor del libro: ");
        scanf("%s", aux->autor);
        
        printf("Entre el número de páginas del libro: ");
        scanf("%d", &aux->paginas);
        
    }
    
    int masLibros = 0;
    
    printf("Quieres adicionar mas libros. Cuántos?: ");
    scanf("%d", &masLibros);
    
    
    if (masLibros > 0) {
        biblioteca = (libro *) realloc(biblioteca, sizeof(libro) * (cantidad + masLibros));
        
        final = biblioteca + cantidad + masLibros;
        
        for (aux = biblioteca + cantidad; aux < final; ++aux) {
            
            aux->titulo = (char * ) malloc(sizeof(char) * 25);
            
            printf("Entre el título del libro: ");
            scanf("%s", aux->titulo);
            
            aux->autor = (char * ) malloc(sizeof(char) * 25);
            
            printf("Entre el autor del libro: ");
            scanf("%s", aux->autor);
            
            printf("Entre el número de páginas del libro: ");
            scanf("%d", &aux->paginas);
            
        }
        
    }
    
    // Mostrar los libros
    printf("\n\n--- Listado de libros ---\n\n");
    for (aux = biblioteca; aux < final; ++aux) {
        printf("%25s \t %25s \t %4d \n",
               aux->titulo,
               aux->autor,
               aux->paginas);
    }
    
    // Liberar la memoria
    
    for (aux = biblioteca; aux < final; ++aux) {
        free(aux->titulo);
        free(aux->autor);
    }
    
    free(biblioteca);
    
    return 0;
}

