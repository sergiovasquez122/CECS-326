#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
	printf("PID of ex1.c = %d\n", getpid());
	char *args[] = {"Hello", "WORLD!", ":)", NULL};
	execv("./ex2.o", args);
	printf("Back to ex1.c");
	return 0;
}
