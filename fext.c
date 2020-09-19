#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	fork();
	fork();
	fork();
	printf("Hello World!\nPID = %d\n", getpid());
	return 0;
}
