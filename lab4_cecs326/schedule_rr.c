/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#include "task.h"
#include "list.h"
#include "cpu.h"


/*
 * Your code and design here:
 */
extern struct node* head;

void add(char *name, int priority, int burst){
    struct task* new_task = malloc(sizeof(struct task));
    new_task->name = name;
    new_task->priority = priority;
    new_task->burst= burst;
    insert(&head, new_task);
}

void schedule(){
    traverse(head);
    while(head != NULL){
	    struct node* iter = head;
	    while(iter != NULL){
		    struct task* current_task = iter->task;
		    if(current_task->burst <= QUANTUM){
			    run(current_task, current_task->burst);
			    printf("task [%s] finished.\n", current_task->name);
			    delete(&head, current_task);
		    } else {
			run(current_task, QUANTUM);
			current_task->burst -= QUANTUM;
		    }
		    iter = iter->next;
	    }
    }
}
