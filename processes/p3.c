#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


/**
 * the exec() will run a different program altogether than fork() which will create a copy of a process. the exec() does not create a new process but replaces the current one. notice also that the value of the child after the exec is not printed. there is no reason that it be expected too since after the exec the process is now replaced.
 */
int main(int argc, char *argv[]){
	printf("hello world (pid:%d)\n", (int) getpid());
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);	
	} else if(rc == 0){
		printf("hello, I am child (pid:%d)\n", (int) getpid());
		char* myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("p3.c");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
		printf("farewell cruel world!"); // this won't print out
	} else {
		int rc_wait = wait(NULL);
		printf("hello, I am parent of %d (rc_wait(%d) (pid:%d)\n",rc , rc_wait, (int) getpid());
	}
	return 0;
}

