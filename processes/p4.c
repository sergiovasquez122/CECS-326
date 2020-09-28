#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>


/**
 * What does this program do:
 *
 * this program first create a new process.
 * the child process then closes the stdout
 * so that we and reopens it for the file so that
 * we the output of the program will be redirected
 * to the file specified. the parent simply waits for
 * the child to finish.
 */
int main(int argc, char *argv[]){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0){
		close(STDOUT_FILENO);
		open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
		char* myargs[3];
		myargs[0] = strdup("wc");
		myargs[1] = strdup("p4.c");
		myargs[2] = NULL;
		execvp(myargs[0], myargs);
	} else {
		int rc_wait = wait(NULL);
	}
	return 0;
}
