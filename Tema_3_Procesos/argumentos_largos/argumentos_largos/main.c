//
//  main.c
//  argumentos_largos
//
//  Created by Vicente Cubells Nonell on 31/08/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Bandera utilizada por ‘--detalles’. */
static int detalles_flag = 0;

/* Bandera utilizada por ‘--resumen’. */
static int resumen_flag = 0;

int main(int argc, char * argv[]) {

    int c;
    
    while (1)
    {
        static struct option long_options[] =
        {
            /* En estas opciones se establece una bandera */
            {"detalles", no_argument,       &detalles_flag, 1},
            {"resumen",   no_argument,       &resumen_flag, 1},
            /* Estas opciones no utilizan una bandera, las identificamos por sus índices */
            {"insertar",     no_argument,       0, 'i'},
            {"adicionar",  	no_argument,       0, 'a'},
            {"borrar",  		required_argument, 0, 'b'},
            {"crear",  		required_argument, 0, 'c'},
            {"archivo",    	required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };
        /* Variable que almacena el índice de la opción */
        int option_index = 0;
        
        c = getopt_long (argc, argv, "aib:c:f:", // "iab:f:c:
                         long_options, &option_index);
        
        /* -1 indica que no hay más opciones */
        if (c == -1)
            break;
        
        switch (c)
        {
            case 0:
                /* Si la opción establece una bandera, no hacemos nada aquí */
                if (long_options[option_index].flag != 0)
                    break;
                printf ("opción %s", long_options[option_index].name);
                if (optarg)
                    printf (" con argumento %s", optarg);
                printf ("\n");
                break;
                
            case 'i':
                puts ("opción -i\n");
                break;
                
            case 'a':
                puts ("opción -a\n");
                break;
                
            case 'b':
                printf ("opción -b con valor '%s'\n", optarg);
                break;
                
            case 'c':
                printf ("opción -c con valor  '%s'\n", optarg);
                break;
                
            case 'f':
                printf ("opción -f con valor  '%s'\n", optarg);
                break;
                
            case '?':
                /* getopt_long ya imprime un mensaje de error. */
                break;
                
            default:
                abort();
        }
    }
    
    /* En lugar de reportar  ‘--detalles'  y ‘--resumen', reportamos su estado final */
    if (detalles_flag)
        puts ("bandera detalles está activa");
    
    if (resumen_flag)
        puts ("bandera resumen está activa");
    
    /* Imprimir cualquier argumento restante (no son opciones) */
    if (optind < argc)
    {
        printf ("elementos que on son opciones: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
    }
    
     return 0;
}
