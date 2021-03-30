#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>

#define WRITER 0
#define READER 1

int main(void)
{
	int shmid;
	char *shmaddr;
	int ret;
	char *message;
	int i=0;

	//get shared memory id
	shmid = shmget((key_t)1234,1024,IPC_CREAT|0666);
	if(shmid == -1)
	{
		perror("shared memory access is failed\n");
		return 0;
	}

	//attach the shared memory
	shmaddr = shmat(shmid, (void *)0,0);
	if(shmaddr ==(char *)-1)
	{

		perror("attach failed\n");
		return 0;
	}

	//메세지는 shmaddr+1부터. 
	message = shmaddr +1;
	//시작은 writer
	shmaddr[0] = WRITER;

	while(1)
	{	
		//reader일 때 읽기
		if(shmaddr[0]==READER)
		{

			printf("The %dth received message from shared memory: %s\n", i, message);
			//읽은 후 writer로 고치기
			shmaddr[0]=WRITER;
			if(!strcmp(message, "bye"))
			{
				break;
			}
			i++;
		}
	

	}
	
	//remove the shared memory
	ret = shmdt(shmaddr);
    if(ret == -1)
	{
    	perror("detach failed\n");
        return 0;
    }
	ret = shmctl(shmid, IPC_RMID, 0);
	if(ret == -1)
	{
		perror("remove faild\n");
		return 0;
	}


	return 0;
}

