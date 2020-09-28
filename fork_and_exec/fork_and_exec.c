#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	pid_t pid = fork();
	if(pid < 0){
		perror("fork failed.");
		exit(1);
	} else if(pid == 0){
		char* args[] = {"./bogosort", "1", "2", "3", NULL};
		execv(args[0], args);
	}
	return 0;
}
