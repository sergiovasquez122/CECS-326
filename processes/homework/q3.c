#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * Write another program using fork(). The child process
 * should print "hello";the parent process should print
 * "goodbye".You should try to ensure taht the child
 * process always prints first;
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
	} else if(rc == 0){
		printf("hello\n");
	} else {
		wait(NULL);
		printf("goodbye\n");
	}
	return 0;
}
