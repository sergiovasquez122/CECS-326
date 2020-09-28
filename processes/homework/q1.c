#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/*
 * Problem statement:
 * Write a program that calls fork(). Before calling fork(), have the main process a varible and set its value to something. what value is the variable in the child process? what happens to the variable when both the child and parent change the value of x?
 */
int main(){
	int x = 100;
	int rc = fork();
	if(rc < 0){
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0){
		printf("the value that the child saw: %d\n", x);
		x = 50;
		printf("the child changed the value to 50, here it is: %d\n", x);

	} else{
		printf("the value that the parent saw: %d\n", x);
		x = 25;
		printf("the parent changed the value to 25, here it is: %d\n", x);
	}
	return 0;
}

