//
//  main.c
//  mpi_scatter
//
//  Created by Vicente Cubells on 31/05/21.
//

#include "mpi.h"
#include <stdio.h>

#define MAXSIZE 100000

int main(int argc, const char * argv[]) 
{
    int myid, numprocs;
    int data[MAXSIZE];
    int i, n, x, myresult = 0, result = 0;
    double start, stop;
    char hostname[MPI_MAX_PROCESSOR_NAME];
    int  longitud;
    
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    
    MPI_Get_processor_name(hostname, &longitud);
    
    n = MAXSIZE;
    /* Inicializar datos */
    if (myid == 0) {
        for(i = 0; i < n; i++) {
            data[i] = 1;
        }
    }
    
    if (myid == 0 ) start = MPI_Wtime();
    
    /* Enviar un porción de los datos a cada proceso */
    x = n/numprocs;

    int data_rec[x];

    MPI_Scatter(data, x, MPI_INT, data_rec, x, MPI_INT,0, MPI_COMM_WORLD);
    
    for(i = 0; i < x; i++) {
        myresult += data_rec[i];
    }
    printf("Yo soy el procesador %d (%s)  y mi suma = %d\n", myid , hostname, myresult);
    
    /* Suma global mediante reducción */
    MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (myid == 0) {
        stop = MPI_Wtime();
        printf("La suma total del vector es = %d.\n", result);
        printf("Tiempo de ejecución de la sección paralela = %f \n", stop-start);
    }
    
    MPI_Finalize();
    
    return 0;
}
