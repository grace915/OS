#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

#define MSG_SIZE 200
#define PIPENAME "./named_pipe_file"

int main(void)
{
    
	char msg[MSG_SIZE];
	char message[200];
	int fd;
	int ret, i;
	
    
	fd = open(PIPENAME, O_WRONLY);
    
	if(fd<0)
	{
		printf("Open failed\n");
		return 0;
	}

	printf("This is A procrss. I'll give the data to B.\n");

	// write message
	while(1)
	{
		sleep(1);
		fgets(message,sizeof(message),stdin);
		//delete last \n
		message[strlen(message)-1] = '\0';
		// msg buffer에 message 넣기
		snprintf(msg,sizeof(msg),"%s",message);
		// write msg
		ret = write(fd, msg, sizeof(msg));
		if(ret<0)
		{
			printf("Write failed\n");
			return 0;
		}
		if(!strcmp(message, "bye"))
		{	
			printf("this message will be sent to b process...\n");
			break;
		}	
	}
	return 0;
}

