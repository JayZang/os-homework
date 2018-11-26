#include "pidManager.h"

int allocate_map() {  
    pidStatus = (unsigned char *)malloc(PID_MAX_COUNT);

    if (!pidStatus) {
        return -1;
    }
    
    memset(pidStatus, 0, PID_MAX_COUNT);

    return 1;
}

int allocate_pid() {
    if (!pidStatus) {
        return -1;
    }

    for (int i = 0; i < PID_MAX_COUNT; i++) {
        if (pidStatus[i] == 0) {
            pidStatus[i] = 1;
            return MIN_PID + i;
        }
    }

    return -1;
}

void release_pid(int pid) {
    if (!pidStatus || pid < MIN_PID || pid > MAX_PID) {
        return;
    }

    pidStatus[pid - MIN_PID] = 0;
}