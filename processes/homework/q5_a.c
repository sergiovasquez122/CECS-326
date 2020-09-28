#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Write a program that uses wait() to wait fo r
 * the child process to finish in the parent.
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
	} else if(rc == 0){
		printf("hello there! I am the child (pid:%d)\n", (int)getpid());	
	} else{
		pid_t result = wait(NULL);
		printf("the result of waiting: %d\n", (int)result);
	}
	return 0;
}
