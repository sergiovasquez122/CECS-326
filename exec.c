#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("hello exec.c\n");
	printf("My pid is %d\n", getpid());
	printf("My arguments ");
	for(int i = 0;i < argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");
	return 0;
}
