#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Write a program that has the child wait.
 * what is the result of the wait.
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
	} else if(rc == 0){
		printf("hello there! I am the child (pid:%d)\n", (int) getpid());
		pid_t result = wait(NULL);
		printf("the result of waiting: %d\n", (int) getpid());
	} else{
		printf("hello there! I am parent (pid%d)\n", (int) getpid());
	}
	return 0;
}
