#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

int shareVariable = 0;

void* simpleThread(void* which){
    int num, val;
    int which_value = *(int *) which;
    num = 0;
    for(;num < 20;num++){
        if(random() > RAND_MAX / 2){
            usleep(500);

            val = shareVariable;
            printf("*** thread %d sees value %d\n", which_value, val);
            shareVariable = val + 1;
        }
        val = shareVariable;
        printf("Thread %d sees final value %d\n", which_value, val);
    }
    pthread_exit(NULL);
}

bool valid_input(char* argv){
    int i = 0;
    for(;argv[i];i++){
        if((argv[i] - '0') < 0 || (argv[i] - '0') > 9){
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv) {
    if(argc < 2){
        printf("usage %s <number of threads>\n", argv[0]);
        exit(-1);
    }
    if(!valid_input(argv[1])){
        printf("the second parameter must be an integer\n");
        exit(-1);
    }
    int number_of_threads = atoi(argv[1]);
    pthread_t threads[number_of_threads];
    int i = 0;
    for(;i < number_of_threads;i++){
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&threads[i], &attr, simpleThread, &i);
    }

    i = 0;
    for(;i < number_of_threads;i++){
        pthread_join(threads[i], NULL);
    }
}
