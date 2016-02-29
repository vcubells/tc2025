#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    int fd;
    fd = open("/tmp/riven", O_RDONLY);

    int num = -1;
    while(num != 0)
    {
        read(fd, &num, sizeof(int));
        if(num != 0)
        {
            int mult = 1;
            for(int i = 1; i <= num; ++i)
            {
                mult *= i;
            }
            printf("El factorial es %d\n", mult);
        }
    }
    close(fd);
}
