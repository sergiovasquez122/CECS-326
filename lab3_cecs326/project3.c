//Sergio Vasquez, Kuldeep Gohil 
//CECS 326
//Lab 3

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int arr[] = {3,5,2,3,5,1,6,4,3,4,6,7,3,4,1,2,3,3,423,543,123,5234,235,643,643,123, 156};		//array in descending order
int n = sizeof(arr) / sizeof(arr[0]);			//array is divided by the position 0 of array 

struct structure{					//structure variables
    int lo, hi;			
};

void* insertion_sort(void* arg){			//insertion sort function 
    struct structure a = *(struct structure* ) arg;	//variable a is equal to thread 
    int lo = a.lo;					//lo variable is equal to lo of a input
    int hi = a.hi;					//hi variable is equal to hi of a input
    for(int i = lo + 1;i < hi;i++){			//for loop runs until i is greater than hi 
        for(int j = i;j > lo && arr[j] < arr[j - 1];j--){
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
    return NULL;					//ends function after getting out of for loop
}

void* merge(void* arg){				//merge function
    struct structure a = *(struct structure*) arg;
    int b_idx = 0;					//used for if statement 
    int left = 0;					//used for if statement 
    int right = a.hi;					//right variable is equal to hi of a input 
    int b[n];					
    while(left < a.hi && right < n){			//while loop that runs if a.lo is less than 0 and a.hi is less than n variable
    
        if(arr[left] < arr[right]){           	//if statement runs if array of 0 is less than array of right value
            b[b_idx++] = arr[left++];
        } else {					//else statement 
            b[b_idx++] = arr[right++];	
        }
    }

    while(left < a.hi) b[b_idx++] = arr[left++];	//while statement of when a.hi is less than 0
    while(right < n) b[b_idx++] = arr[right++];	//while statement of when a.hi is less than n value

    for(int i = 0;i < n;i++)				//for loop which assigns array i value to b of i
        arr[i] = b[i];
    return NULL;
}

int main() {						//main function
    struct structure structures[2];			//lists number of structures
    structures[0].lo = 0;				//when lo is 0, then it equals 0
    structures[0].hi = n / 2;				//when hi is 0, then it equals n divided by 2
    structures[1].lo = structures[0].hi;		//when lo is 1, then it equals value of hi when its 0
    structures[1].hi = n;				//when hi is 1, then it equals n
    pthread_t threads[2];				//lists numbers of pthreads to sort each sublist
    for(int i = 0;i < 2;i++)				//for loop for insertion_sort thread creation 
        pthread_create(&threads[i], NULL, insertion_sort, &structures[i]);


    for(int i = 0;i < 2;i++)				//for loop for the threads waiting 
        pthread_join(threads[i], NULL);

    pthread_t merge_thread;				//thread that merges the two sublist into a single sorted list
    pthread_create(&merge_thread, NULL, merge, &structures[0]);	//thread merges
    pthread_join(merge_thread, NULL);			//merge thread waits
    for(int i = 0;i < n;i++){				//used to print the outputs 
        printf("%d ", arr[i]);
    }
    printf("\n");					
}
