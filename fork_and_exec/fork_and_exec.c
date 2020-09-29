#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>

#define NUM_CHILDREN 2

int main(int argc, char* argv[]){
	for(int i = 0;i < NUM_CHILDREN;i++){
		pid_t pid = fork();
	if(pid < 0){
		perror("fork failed.");
		exit(1);
	} else if(pid == 0){
		char* args[] = {"./bogosort", "1", "2", "3", NULL};
		execv(args[0], args);
		}
	}
	// parent wait for child
	for(int i = 0;i < NUM_CHILDREN;i++)	
		wait(NULL);
	return 0;
}
