#include <stdio.h>
#include <unistd.h>

int favorite_number = 52;

int main(int argc, char* argv[]){
	printf("exec_call.c\n");
	printf("my favorite_number is %d\n", favorite_number);
	printf("My pid is %d\n", (int) getpid());
	char* args[] = {"Hello", "World", NULL};
	execv("./exec_demo.o", args);
	return 0;
}
