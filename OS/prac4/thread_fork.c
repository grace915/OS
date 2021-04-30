#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *t_function(void *date)
{
	sleep(50);
}
int main()
{
	pthread_t p_thread;

	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		fork();
		pthread_create(&p_thread, NULL, t_function, (void*)NULL);
	}
	fork();

	sleep(100);
	return 0;
}
