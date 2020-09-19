#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	printf("PID of something.c = %d\n", getpid());
	execv("/usr/bin/apt-get", argv);
	return 0;
}
