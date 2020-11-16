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
    bool finished = false;
    while(!finished){
        struct node* iter = head;
        bool no_task_to_complete = true;
        while(iter != NULL){
            struct task* current_task = iter->task;
            if(current_task->burst <= QUANTUM && current_task->burst > 0){
                no_task_to_complete = false;
                run(current_task, current_task->burst);
                current_task->burst = 0;
                printf("task [%s] finished.\n", current_task->name);
            } else if(current_task->burst > QUANTUM){
                no_task_to_complete = false;
                run(current_task, QUANTUM);
                current_task->burst -= QUANTUM;
            }
            iter = iter->next;
        }
        finished = no_task_to_complete;
    }

    while(head != NULL){
        struct task* current_task = head->task;
        delete(&head, current_task);
    }
}
