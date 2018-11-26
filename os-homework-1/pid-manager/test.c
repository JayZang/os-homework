#include "stdlib.h"
#include "pidManager.h"

void allocate();

int main()
{
    if (allocate_map() == -1) {
        printf("Init PID map failed\n");
        return -1;
    }

    allocate();         // 300
    allocate();         // 301
    release_pid(301);   
    allocate();         // 301
    allocate();         // 302
    release_pid(300);   
    allocate();         // 300
    allocate();         // 303
}

void allocate() {
    int pid = allocate_pid();
    
    if (pid == -1) {
        printf("Allocate PID failed\n");
        return;
    }
    else {
        printf("PID : %d\n", pid);
    }
}