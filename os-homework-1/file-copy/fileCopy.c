#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCK_SIZE 1024

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Miss source file and distination file\n");
        return -1;
    }
    else if (argc < 3 ) {
        printf("Missing distination file\n");
        return -1;
    }

    int srcFile = -1, dstFile = -1;
    ssize_t bytes_read = -1;
    char buff[BLOCK_SIZE];
    char *srcFilePath = argv[1];
    char *dstFilePath = argv[2];

    srcFile = open(srcFilePath, O_RDONLY);
    if (srcFile == -1)
    {
        printf("Open source file Failed\n");
        return -1;
    }

    dstFile = open(dstFilePath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (dstFile == -1)
    {
        printf("Create distination file Failed\n");
        return -1;
    }

    while ((bytes_read = read(srcFile, buff, BLOCK_SIZE)) > 0)
    {
        write(dstFile, buff, bytes_read);
    }

    close(srcFile);
    close(dstFile);
    printf("Copy successfully\n");
}