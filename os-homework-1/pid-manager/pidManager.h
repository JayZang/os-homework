#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MIN_PID 300
#define MAX_PID 5000
#define PID_MAX_COUNT (MAX_PID - MIN_PID + 1)

unsigned char *pidStatus;
int allocate_map();
int allocate_pid();
void release_pid(int);