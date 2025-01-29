#include "pipex.h"
#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int main(void)
{
    int number;
    int fd = open("fifofile", O_RDONLY);
    int readbyte = 1;
    int sum = 0;
    while (1)
    {
        readbyte = read(fd, &number, sizeof(int)) != 0;
        if (readbyte == -1)
        {
            printf("error reading fifo file!\n");
            return 1;
        }
        if (readbyte == 0)
            break;
        sum += number;
    }
    close(fd);
    fd = open("fifofile", O_WRONLY);
    printf("writing the sum into fifo file\n");
    if (write(fd, &sum, sizeof(sum)) == -1)
    {
        printf("error writing into fifo file!\n");
        return 1;
    }
    close(fd);
    return 0;
}
