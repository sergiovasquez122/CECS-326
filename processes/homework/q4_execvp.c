#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
 * Write a program that calls fork() and then 
 * calls some form of exec() to run the program
 * /bin/ls.
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
	} else if(rc == 0){
		char* args[2];
		args[0] = strdup("/bin/ls");
		args[1] = NULL;
		execvp(args[0], args);
	} else {
		int rc = wait(NULL);
	}
	return 0;
}
