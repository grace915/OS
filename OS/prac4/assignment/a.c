#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARGUMENT_NUMBER 20

long long result = 0;
long long dab[ARGUMENT_NUMBER];

void *ThreadFunc(void *n)
{
    long long i;
   
    long long number = *((long long *)n);
    printf("number = %lld\n", number);
    for(i=0; i<25000000;i++){
        dab[number] += number;
    }
}

int main(void)
{
    pthread_t threadID[ARGUMENT_NUMBER];
    long long argument[ARGUMENT_NUMBER];
    long long i;

    for(i=0; i<ARGUMENT_NUMBER;i++){
        argument[i] = i;
    }
    for(i=0; i<ARGUMENT_NUMBER; i++){
       pthread_create(&(threadID[i]), NULL, ThreadFunc, (void *)&argument[i]);
    }
    printf("Main Thread is waiting for Child Thread!\n");
    for(i=0; i<ARGUMENT_NUMBER; i++){
        pthread_join(threadID[i],NULL);
    }

    for(i=0;i<ARGUMENT_NUMBER;i++){
        result+=dab[i];
    }

    printf("result = %lld\n", result);
    
    return 0;
}