/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "task.h"
#include "list.h"
#include "cpu.h"


//Your code and design here
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
        struct task* current_task = head->task;
        run(current_task, current_task->burst);
        delete(&head,  current_task);
    }
}
