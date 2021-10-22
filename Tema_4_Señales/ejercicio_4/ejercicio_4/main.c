//
//  main.c
//  ejercicio_4
//
//  Created by Vicente Cubells on 24/09/20.
//

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void gestor_ctrlc1(int sid)
{
    printf("Estoy aprendiendo a manejar señales...\n");
}

void gestor_ctrlc2(int sid)
{
    printf("Ahora cambié de manejador...\n");
}

void contar(char * texto,  void (* handler_t)(int))
{
    struct sigaction gestor;
    
    //gestor.sa_handler = handler_t ; // signal(SIGINT, handler_t);
    
    signal(SIGINT, handler_t);
    
    //sigaction(SIGINT, &gestor, NULL);
    
    int i = 1;
    
    while (i <= 10) {
        printf("%d %s...\n", i++, texto);
        sleep(1);
    }
        
}

int main(int argc, const char * argv[]) {
    
    /* Obtener manejador previo */
    //printf("Guardando manejador inicial...\n");
    //struct sigaction gestor;
    
    //sigaction(SIGINT, NULL, &gestor);
    
    /* Bloque 1 Contando ovejitas */
    contar("ovejitas", gestor_ctrlc1);
    
    /* Bloque 2 Contando trineos */
    contar("trineos", gestor_ctrlc2);
    
    /* Bloque 3 Contando cabritas */
    contar("cabritas", gestor_ctrlc1);
    
    /* Restaurar manejador inicial */
    printf("Restaurando manejador inicial...\n");
    //sigaction(SIGINT, &gestor, NULL);
    
    return 0;
}
