#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	printf("PID of ex1.c = %d\n", getpid());
	execv("/bin/ls", argv);
	printf("back to me\n");
	return 0;
}
