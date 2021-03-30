#include <stdio.h>
#include <unistd.h>
int main(){
	
		
	FILE *fp = fopen("test.txt", "r");
	for(int i = 0; i<6; i++){	
		char a[10];
		fseek(fp, 0, SEEK_SET);
		fflush(fp);
		fgets(a, 10, fp);
		printf("%s",a);
		sleep(2);
		
	}
	fclose(fp);
	

	return 0;
}
