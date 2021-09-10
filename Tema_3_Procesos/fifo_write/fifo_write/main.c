//
//  main.c
//  fifo_write
//
//  Created by Vicente Cubells Nonell on 07/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[])
{
    
    int error = mkfifo("/Users/vcubells/fifo", 0777);
    
    if (error) {
        printf("Error al crear el FIFO\n");
        exit(-1);
    }
    
    int fd = open("/Users/vcubells/fifo", O_WRONLY);
    
    int i = 0;
    
    while (i != -1) {
        printf("Entra un número: ");
        scanf("%d", &i);
        
        write(fd, &i, sizeof(int));
    }
    
    close(fd);
    unlink("/Users/vcubells/fifo");
    
    return 0;
}

