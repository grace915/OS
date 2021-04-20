#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>

#define COUNTING_NUMBER 2000000


//structure 
struct smStruct
{
	int processidassign;
	int turn;
	int flag[2];
	int critical_section_variable;

};


//본인것 1, turn은 상대방. while(flag[상대방] and turn == 상대방) 
void lock(struct smStruct *smstruct, int order)
{
	smstruct->flag[order] = 1;
	smstruct->turn = 1-order;
	while(smstruct->flag[1-order]==1 && smstruct->turn==1-order);
}
// 본인것 0
void unlock(struct smStruct *smstruct, int order)
{
	smstruct->flag[order]=0;
}

int main(void)
{
	//값을 증가시키는 행위를 실제로 카운팅하는 localcount
	int localcount =0;
	
	struct smStruct *smstruct = NULL;

	int shmid;
	void *shmaddr;
	int ret;
	int Myorder = 0;
	//get shared memory id or create		
	shmid = shmget((key_t)1234,1024,IPC_CREAT|0666);
	if (shmid ==-1)
	{
		perror("shmget failed\n");
		exit(0);
	}
	//attach shared memory 
	shmaddr = shmat(shmid,(void*)0,0);
	if(shmaddr == (char*)-1)
    {
        perror("failed attact address\n");
        return 0;
    }
	smstruct = shmaddr;

	//processidassign이 0이 아니라는 뜻은 이미 하나의 child process가 access해있다는 뜻이다.
	if(smstruct->processidassign != 0){
		Myorder = 1;
	}
	//idassign도 lock, unlock 필요
	lock(smstruct, Myorder);
	smstruct->processidassign = getpid();
	unlock(smstruct, Myorder);
	// 순서, id 값 출력
	printf("Myorder = %d, process pid = %d\n", Myorder, smstruct->processidassign);
	
//allow only one thread at a time to increase the critical_section_variable to COUNTING_NUMBER	
	for(int i=0;i<COUNTING_NUMBER;i++)
	{
		localcount++;
		lock(smstruct, Myorder);
		//processidassign에 myorder 값을 넣기
		smstruct->critical_section_variable++;
		unlock(smstruct,Myorder);
	}
	
	// local count 값 출력
	printf("child finish! local count = %d\n", localcount);
	
	//detach shared memory
	ret = shmdt(shmaddr);
	if(ret == -1)
	{
		perror("detach failed\n");
		return 0;
	}
	


	return 0;

}