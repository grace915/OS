#include <stdio.h>
#include <unistd.h>

int main(void)
{
	execl("./exec_practice", NULL);
	printf("This sentence must not be print!\n");
	return 0;

}
