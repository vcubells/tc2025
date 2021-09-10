//
//  main.c
//  fifo_read
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


unsigned long int factorial (int num);

int main(int argc, const char * argv[])
{
    int fd;
    int leidos = 1;
    
    fd = open("/Users/vcubells/fifo", O_RDONLY);
    
    int i = 0;
    
    while (i != -1) {
        leidos = read(fd, &i, sizeof(int));
        
        printf("%d! = %d \n", i, factorial(i));
    }
    
    close(fd);
    
    return 0;
}

unsigned long int factorial (int num)
{
    unsigned long int f = 1;
    int i;
    for(i = 2; i <= num; ++i)
        f *= i;
    
    return f;
}
