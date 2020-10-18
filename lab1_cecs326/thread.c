#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>					//allows usage of pthreads 
#include <unistd.h>
#include <stdbool.h>


pthread_mutex_t mutex; 				//declaring mutex variable 
pthread_barrier_t barrier; 				//declaring barrier variable 
int shareVariable = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	//initializes static mutex 

void* simpleThread(void* which){			//function randomly 

    int num, val;
    int* which_ptr = (int *) which;
    num = 0;
    for(;num < 20;num++){
          if(random() > RAND_MAX / 2)
            usleep(500);
#ifdef PTHREAD_SYNC
        pthread_mutex_lock(&mutex);			//locks mutex
#endif

            val = shareVariable;
            printf("*** thread %d sees value %d\n", *which_ptr, val);
            shareVariable = val + 1;			//increments shareVariable by 1 
            
#ifdef PTHREAD_SYNC
        pthread_mutex_unlock(&mutex);			//unlocks mutex
#endif
    }
#ifdef PTHREAD_SYNC
        pthread_barrier_wait(&barrier);		//synchronizes the threads until they all equal same final value  
#endif
        val = shareVariable;
        printf("Thread %d sees final value %d\n", *which_ptr, val);
    pthread_exit(NULL);
}

bool valid_input(char* argv){					//function validates user input 
    int i = 0;
    for(;argv[i];i++){
        if((argv[i] - '0') < 0 || (argv[i] - '0') > 9){
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv) {				//main function
    if(argc < 2){
        printf("usage %s <number of threads>\n", argv[0]);
        exit(-1);
    }
    if(!valid_input(argv[1])){
        printf("the second parameter must be an integer\n");
        exit(-1);
    }
    int number_of_threads = atoi(argv[1]);			//assigning user input to variable number_of_threads
    pthread_t threads[number_of_threads];
    int ids[number_of_threads];				
    
    #ifdef PTHREAD_SYNC
    pthread_mutex_init(&mutex, NULL); 				//initializes mutex variable 
    pthread_barrier_init(&barrier, NULL, number_of_threads);		//initializes barrier variable 
    #endif

    for(int i = 0;i < number_of_threads;i++){				
        ids[i] = i;						//thread is given id 
    }

    for(int i = 0;i < number_of_threads;i++){				
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&threads[i], &attr, simpleThread, &ids[i]);	//threads are created 
    }

    for(int i = 0;i < number_of_threads;i++){				//for loop waits for threads to finish 
        pthread_join(threads[i], NULL);
    }
    return 0;
}
