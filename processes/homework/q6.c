#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Write a slight modification of the previous program,
 * this time using waitpid() instead of wait().
 * when would waitpid() be useful?
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
	} else if(rc == 0){
		printf("hello there! I am the child (pid:%d)\n", (int) getpid());
		return -1;
	} else{
		int status;
		int result = waitpid(rc, &status, 0);
		printf("the value of result: %d\n", result);
		printf("the value of status: %d\n", WEXITSTATUS(status));
	}
	return 0;
}
