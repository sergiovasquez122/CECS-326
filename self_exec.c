#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	printf("my pid is %d\n", (int) getpid());
	char *args[] = {"./self_exec.o", "I'm", "back", NULL};
	execvp(args[0], args);
	printf("farewell cruel world");
	return 0;
}
