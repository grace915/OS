#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<wait.h>
#define COUNTING_NUMBER 2000000

//structure 
struct smStruct
{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;

};

int main()
{
	//자식 프로세스 2개
	pid_t pid1;
	pid_t pid2;
	int status;

	struct smStruct *smstruct=NULL;
	
	int shmid;
	void *shmaddr;
	int ret;
	//get shared memory id or create
	if((shmid = shmget((key_t)1234,1024,IPC_CREAT|0666))==-1)
    {
        perror("shmget failed\n");
        return 0;
	}
	//attach the shared memory
    shmaddr= shmat(shmid, (void*)0,0);
    if(shmaddr == (char*)-1)
    {
        perror("failed attact address\n");
        return 0;
    }
	//구조체 값 설정
    smstruct = shmaddr;
	smstruct->turn=0;
	smstruct->processidassign=0;
    smstruct->critical_section_variable = 0;
	smstruct->flag[0]=0;
	smstruct->flag[1]=0;

	//create child processes and run 
	if((pid1=fork())==0)
	{
		execl("./child","./child",NULL);
		exit(0);
	}

	if((pid2=fork())==0)
	{
		execl("./child","./child",NULL);
		exit(0);
	}
	else
	{
		waitpid(pid1,&status,0);
		waitpid(pid2,&status, 0);
	}

	// 자식 프로세스 종료 후 critical section variable 값 출력
	printf("Actual Count: %d | Expected Count: %d\n",smstruct->critical_section_variable, COUNTING_NUMBER*2);

	//detach shared memory
	ret = shmdt(shmaddr);
	if(ret == -1)
	{
		perror("detach failed\n");
		return 0;
	}
	//delete shared memory
	ret = shmctl(shmid,IPC_RMID, 0);

	if(ret == -1)
	{
		perror("remove failed\n");
		return 0;

	}

	return 0;
}