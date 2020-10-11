#include <cstring>
#include <stdlib.h>
#include <stdio.h>

int capacity, occupancy = 0;
bool question, answer;
pthread_mutex_t lock;
pthread_cond_t full_cv, question_asked_cv, question_answered_cv;

/**
 * It is the turn of the student i to ask his/her next question.
 * print 'Student x asks a question.'
 * Wait to print out the message until it is really that student's turn
 */
void QuestionStart(){

}

/**
 * The student is satisfied with the answer to his most recent question.
 * print 'Student x is satisfied'.
 * QuestionDone() should not print anything until the professor has finished answering the question.
 */
void QuestionDone(){

}

/**
 * The professor starts to answer a question of a student.
 * Print 'Professor starts answer question for student x'
 */
void AnswerStart(){

}

/**
 * The professor is done answering a question of a student.
 * Print 'Professor is done with answer for student x'
 */
void AnswerDone(){

}

/**
 * It is the student's turn to enter the professor's office to ask questiosn.
 * print 'Student x shows up in the office'
 */
void EnterOffice(){

}

/**
 * The student has no more questions to ask, so he/she leaves the professor's office
 * print 'Student x leaves the office.'
 */
void LeaveOffice(){

}

/**
 * This function creates a thread that represents a new student with identifier id
 * that asks the professor one or more questions. First, each
 * student need to enter the professor's office by calling EnterOffice().. If the office already
 * full, the student must wait.
 */
void* Student(void* id){

}

/**
 *  This function starts a thread that runs a loop calling AnswerStart()
 *  and AnswerDone(). AnswerStart() blocks when there are no students around
 */
void* Professor(){

}

/**
 * check is the c string represents a number
 * return true if the c string represents a number
 * and false otherwise
 */
bool is_number(const char* arg){
    int n = strlen(arg);
    for(int i = 0;i < n;i++){
        if(arg[i] < '0' || arg[i] > '9'){
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if(argc != 3){
        printf("Usage: %s <# of students> <capacity>", argv[0]);
        exit(-1);
    }
    if(!is_number(argv[1]) || !is_number(argv[2])){
        printf("One of the parameters is not a valid number");
        exit(-1);
    }
    int number_of_students = atoi(argv[1]);
    int capacity = atoi(argv[2]);
    printf("number of students: %d\n", number_of_students);
    printf("total capacity: %d\n", capacity);
}
