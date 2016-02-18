#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char * argv[])
{
    unlink("/tmp/riven");
    int error = mkfifo("/tmp/riven", 0777);
    if(error)
    {
        printf("Error al crear el FIFO con error numero %d\n", error);
        exit(error);
    }

    int num = -1;
    int fd = open("/tmp/riven", O_WRONLY);
    while(num != 0)
    {
        scanf("%d", &num);
        write(fd, &num, sizeof(int));
    }

    close(fd);
    unlink("/tmp/riven");
    return 0;
}
