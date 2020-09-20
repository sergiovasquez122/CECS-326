#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int favorite_number = 42;

int main(int argc, char *argv[]){
	printf("my favorite_number is %d\n", favorite_number);
	char *args[] = {"./exec_call.o", "Hello", "world", NULL};
	execvp(args[0], args);
	printf("Farewell curel world!\n");
	return 0;
}
