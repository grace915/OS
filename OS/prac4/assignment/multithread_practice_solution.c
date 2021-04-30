#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARGUMENT_NUMBER 20

//array for containing computational values for each thread 
long long result[ARGUMENT_NUMBER];

void *ThreadFunc(void *n)
{
    long long i;
    long long number = *((long long *)n);
    printf("number = %lld\n", number);
    for(i=0; i<25000000; i++)
    {
        result[number]+=number;
    }
}

int main(void)
{
    pthread_t threadID[ARGUMENT_NUMBER];

    long long argument[ARGUMENT_NUMBER];
    long long i;

    for(i=0; i<ARGUMENT_NUMBER; i++)
    {
        argument[i] = i;
    }

    //20 threads create
    for(i=0; i<ARGUMENT_NUMBER; i++)
    {
        pthread_create(&(threadID[i]), NULL, ThreadFunc, (void *)&argument[i]);
    }
    printf("Main Thread is waiting for Child Thread!\n");

    //wait for the end of each threads
    for(i=0; i<ARGUMENT_NUMBER; i++)
    {
        pthread_join(threadID[i], NULL);
    }

    //add reuslt of each thread
    long long sum;


    for(i=0; i<ARGUMENT_NUMBER; i++)
    {
        sum+=result[i];
    }
    printf("result = %lld\n", sum);
    return 0;
}
