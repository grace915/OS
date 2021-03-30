#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define WRITER 0
#define READER 1

int main(void)
{
	int shmid;
	char *shmaddr;
	char *message;
	int ret;

	shmid =shmget((key_t)1234,1024,IPC_CREAT|0666);
	if(shmid<0)
	{
		perror("shmget");
		return 0;
	}

	shmaddr = shmat(shmid, (void *)0,0);
    if(shmaddr == (char *)-1)
    {
    	perror("attach failed\n");
        return 0;
    }

	//writer가 값을 썼는지 확인 해줘야 하므로
	shmaddr[0] = WRITER;

	//실질적 문자열 shmaddr + 1부터.
	message = shmaddr +1;

	//while문으로 계속 입력 받기. 입력받을 때는 WRITER여야함. 
	while(1){
		
		if(shmaddr[0] == WRITER)
		{
			fgets(message, 200, stdin);
			message[strlen(message)-1]='\0';
			//입력 받은 후 READER로 바꿔주기
			shmaddr[0]=READER;
			if(!strcmp(message, "bye"))
			{
				break;
			}
		}
			
	}

	ret = shmdt(shmaddr);
	
	if(ret == -1)
	{
		perror("detach failed\n");
		return 0;
	}

	return 0;
}
