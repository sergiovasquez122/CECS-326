#include <stdio.h>
#include <assert.h>
#include <pthread.h>

/**
 * What this program does:
 * the program two threads that will print out
 * a request c-style string. pthread_join will wait
 * for a particular thread to finish, we do two calls
 * to ensure wait for both threads created to finish before
 * the main thread runs again. three threads were employed
 * during this run. the main thread, t1 and t2.
 */
void *mythread(void *arg){
	printf("%s\n", (char *) arg);
	return NULL;
}

int main(int argc, char *argv[]){
	pthread_t p1, p2;
	int rc;
	printf("main: begin\n");
	pthread_create(&p1, NULL, mythread, "A");
	pthread_create(&p2, NULL, mythread, "B");

	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	printf("main: end\n");
	return 0;
}
