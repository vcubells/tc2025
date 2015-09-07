//
//  main.c
//  fifo_write
//
//  Created by Vicente Cubells Nonell on 07/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char * argv[])
{
    
    int error = mkfifo("/Users/vcubells/fifo", 0777);
    
    if (error) {
        printf("Error al crear el FIFO\n");
        exit(-1);
    }
    
    FILE * file;
    
    file = fopen("/Users/vcubells/fifo", "w");
    
    int i = 0;
    
    while (i++ < 10) {
        fprintf(file, "%d", i);
        sleep(1);
    }
    
    fclose(file);
    
    return 0;
}

