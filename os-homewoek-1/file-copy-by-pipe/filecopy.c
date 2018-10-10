#include "stdlib.h"
#include "stdio.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define BLOCK_SIZE 10

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Miss source file and distination file\n");
        return -1;
    }
    else if (argc < 3) {
        printf("Missing distination file\n");
        return -1;
    }

    char buff[BLOCK_SIZE];
    int fd[2];
    pid_t childpid;

    if (pipe(fd) < 0) {
        printf("Create pipe failed!!! \n");
        return -1;
    }

    if ((childpid = fork()) == -1)
    {
        printf("Create sub process failed!!! \n");
        return -1;
    }

    if (childpid == 0) {
        close(fd[1]);

        char *dstFilePath = argv[2];
        int nbytes = -1;

        int dstFile = open(dstFilePath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        if (dstFile == -1) {
            printf("Create distination file Failed\n");
            return -1;
        }

        while((nbytes = read(fd[0], buff, BLOCK_SIZE)) > 0) {
            write(dstFile, buff, nbytes);
        }

        close(dstFile);
    }
    else {
        close(fd[0]);

        char *srcFilePath = argv[1];
        int bytes_read = -1;
        int srcFile = open(srcFilePath, O_RDONLY);
        if (srcFile == -1) {
            printf("Open source file Failed\n");
            return -1;
        }

        while ((bytes_read = read(srcFile, buff, BLOCK_SIZE)) > 0) {
            write(fd[1], buff, bytes_read);
        }

        close(srcFile);
    }
}