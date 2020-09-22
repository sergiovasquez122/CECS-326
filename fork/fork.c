#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int i = 0;

void do_some_work(char* name){
	const int NUM_TIMES = 5;
	for(;i < NUM_TIMES;i++){
		sleep(rand() % 4);
		printf("Done pass %d\n", i);
		printf("%s\n", name);
	}
}

int main(int argc, char* argv[]){
	printf("I am %d\n", (int) getpid());
	pid_t pid = fork();
	if(pid < 0){
		perror("fork failed\n");
		exit(-1);
	}
	if(pid == 0){
		printf("I am child with pid %d\n", (int) getpid());
		do_some_work("child");
		printf("child exiting...\n");
		exit(42);
	} 
	printf("I am the parent\n");
	do_some_work("parent");
	int status = 0;
	pid_t childPid = wait(&status);
	printf("Parent knows child %d has finished with status %d\n", (int) getpid(), status);
	int child_return_value = WEXITSTATUS(status);
	printf("return value was %d\n", child_return_value);
	return 0;
}
