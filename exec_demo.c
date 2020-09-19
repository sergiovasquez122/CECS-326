#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char *args[] = {"./exec_call.o", "Hello", "world", NULL};
	execvp(args[0], args);
	return 0;
}
