/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

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

// invoke the scheduler
void schedule(){
    traverse(head);
    while(head != NULL){
        struct node* iter = head;

        struct task* task_chosen = NULL;
        int highest_priority_task = -1;

        while(iter != NULL){
            struct task* current_task = iter->task;
            if(current_task->priority > highest_priority_task){
                highest_priority_task = current_task->priority;
                task_chosen = current_task;
            }
            iter = iter->next;
        }
        run(task_chosen, task_chosen->burst);
        delete(&head, task_chosen);
    }
}
