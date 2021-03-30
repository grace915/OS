#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	
	FILE *fp = fopen("test.txt", "w");
	for(int i = 0; i<12; i++){
		fseek(fp, 0, SEEK_SET);
		fprintf(fp, "%d\n",i);
		fflush(fp);
		printf("Child1 wrote %d\n",i );
		sleep(1);
		
	}
	fclose(fp);

	return 0;
}
