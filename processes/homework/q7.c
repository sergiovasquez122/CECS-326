#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

/**
 * Write a program that creates a child process, and thn
 * in the child closes standard output. what happens if
 * the childs printf to print some output after closing
 * the descriptor?
 */
int main(){
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0){
		close(STDOUT_FILENO);
		printf("hello world!\n");
	} else {
		int rc = wait(NULL);
		printf("exit....\n");
	}
	return 0;
}
