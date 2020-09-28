#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
/**
 * Write a program that opens a file
 * and then calls fork() to create a new process.
 * can both the child and parent acess the file 
 * descriptor returned by open()? what happens when
 * they are writing to the file concurrently?
 */
int main(){
	close(STDOUT_FILENO);
	open("./q2.output", O_CREAT | O_WRONLY | O_TRUNC | S_IROTH);
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "error occurred\n");
		exit(-1);
	} else if(rc == 0){
		printf("hello I am the child\n");
	} else {
		int rc_wait = wait(NULL);
		printf("hello I am the parent\n");
	}
	return 0;
}
