#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <wait.h>
#define COUNTING_NUMBER 2000000

struct smStruct{
    int processidassign;
    int turn;
    int flag[2];
    int critical_section_variable;

}

int main()
{

}