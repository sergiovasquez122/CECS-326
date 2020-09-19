#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct sum_runner_struct {
	long long ans;
	long long limit;
};

void* sum_runner(void* arg){
	struct sum_runner_struct* the_struct = (struct sum_runner_struct*) arg;
	long long sum = 0;
	long long limit = the_struct->limit;
	for(long long i = 0;i <= limit;i++){
		sum += i;
	}
	the_struct->ans = sum;
	pthread_exit(0);
}

int main(int argc, char** argv){
	if(argc < 2){
		printf("Usage %s num1 num2 .... numn\n", argv[0]);
		exit(-1);
	}
	int arg_num = argc - 1;
	struct sum_runner_struct the_structs[arg_num];
	pthread_t threads[arg_num];
	for(int i = 0;i < arg_num;i++){
		long long limit = atoll(argv[i + 1]);
		the_structs[i].ans = 0;
		the_structs[i].limit = limit;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&threads[i], &attr, sum_runner, &the_structs[i]);
	}

	for(int i = 0;i < arg_num;i++){
		pthread_join(threads[i], NULL);
		printf("The sum of thread %i is %lld\n", i,the_structs[i].ans);
	}
	return 0;
}
