#include <stdio.h>
#include <pthread.h>

#define NUM_LOOPS 5000000

long long sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* counting_functions(void* arg){
	int offset = *(int*) arg;
	for(int i = 0;i < NUM_LOOPS;i++){
		pthread_mutex_lock(&mutex);
		sum += offset;
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

int main(void){
	pthread_t tid1;
	int offset1 = 1;
	pthread_create(&tid1, NULL, counting_functions, &offset1);
	pthread_t tid2;
	int offset2 = -11;
	pthread_create(&tid2, NULL, counting_functions, &offset2);
	pthread_join(tid2, NULL);
	printf("sum = %lld\n", sum);
	return 0;
}
