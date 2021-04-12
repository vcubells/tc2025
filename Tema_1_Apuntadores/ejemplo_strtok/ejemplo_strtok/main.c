//
//  main.c
//  ejemplo_strtok
//
//  Created by Vicente Cubells on 25/03/21.
//

#include <stdio.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    char str[] ="20,5,10,8";
    char * pch;
    printf ("Cadena original: %s\n",str);
    pch = strtok (str,",");
    while (pch != NULL)
    {
      printf ("%s\n",pch);
      pch = strtok (NULL, ",");
    }
    return 0;
}
