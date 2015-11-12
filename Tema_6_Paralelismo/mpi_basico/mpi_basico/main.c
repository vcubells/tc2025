//
//  main.c
//  mpi_basico
//
//  Created by Vicente Cubells Nonell on 12/11/15.
//  Copyright © 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <mpi.h>
#include <stdio.h>

int main(int argc, char * argv[])
{
    int  numtasks, rank, rc;
    
    rc = MPI_Init(&argc,&argv);
    
    if (rc != MPI_SUCCESS) {
        
        printf ("Error al iniciar MPI \n");
        
        MPI_Abort(MPI_COMM_WORLD, rc);
        
    }
    
    // Obteniendo el número de tareas o procesos
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
    
    // Obteniendo el número de la tarea
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    // Obteniendo el nombre del nodo
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    
    printf ("[%s] Proceso %d de %d \n", processor_name, rank, 	numtasks);
    
    
    /*******  hacer algo *******/
    
    
    MPI_Finalize();
    
    return 0;
    
}

