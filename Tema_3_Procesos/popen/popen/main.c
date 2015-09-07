//
//  main.c
//  popen
//
//  Created by Vicente Cubells Nonell on 07/09/15.
//  Copyright (c) 2015 Vicente Cubells Nonell. All rights reserved.
//


#include <stdio.h>

int main(int argc, const char * argv[])
{
    
    FILE * file;
    int i = 0;
    
    file = popen("cat", "w");
    
    while(1)
    {
        fprintf(file, "%d\n", ++i);
    }
    
    pclose(file);
    
    return 0;
}
