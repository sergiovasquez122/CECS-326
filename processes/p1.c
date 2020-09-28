#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * 
 * What's happening in the program.
 * Every process is given a PID or process identifier.
 * In unix the pid is used to name a process in case
 * you want to do something with the process. for example
 * killing a process.
 *
 * the fork command in unix creates a new process.
 * the process is almost an exact copy of the old
 * process but it starts where the fork was called.
 * also notice that the values of rc are different 
 * depending on which process is using it. when the
 * child prints the value of rc we get the integer 0
 * while when the parent prints the value of rc we 
 * get the PID of the child. this differentation helps
 * make the code listed above
 */

int main(int argc, char *argv[]){
	printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();
	if(rc < 0){
		// fork failed
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0){
		printf("hello, I am child (pid:%d)\n", (int) getpid());
		printf("this is the value of rc: %d\n", rc);
	} else {
		printf("hello I am the parent of %d (pid:%d)\n", rc, (int) getpid());
	}
	return 0;
}

