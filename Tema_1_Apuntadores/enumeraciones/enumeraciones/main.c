//
//  main.c
//  enumeraciones
//
//  Created by Vicente Cubells Nonell on 14/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>

enum DiasSemana {
    Domingo, Lunes, Martes, Miercoles, Jueves, Viernes, Sabado
};

int main(int argc, const char * argv[]) {
    
    enum DiasSemana dia;
    
    for (dia = Domingo; dia <= Sabado; ++dia)
    {
        printf("%d, ", dia);
    }
    return 0;
}

