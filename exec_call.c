#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	printf("exec_call.c\n");
	printf("My pid is %d\n", (int) getpid());
	char* args[] = {"Hello", "World", NULL};
	execv("./exec.o", args);
	return 0;
}
