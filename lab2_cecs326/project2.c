#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int capacity, occupancy = 0, current_student;
bool professor = false, student = true;
pthread_mutex_t full_mutex, question_ask_mutex, question_answer_mutex, lock4;
pthread_cond_t full_cv, question_asked_cv, question_answered_cv;

/**
 * It is the turn of the student i to ask his/her next question.
 * print 'Student x asks a question.'
 * Wait to print out the message until it is really that student's turn
 */
void QuestionStart(int student_id){
    printf("Student %d asks a question\n", student_id);
    while(professor) pthread_cond_signal(&question_answered_cv);
    professor = true;
    pthread_cond_wait(&question_asked_cv, &question_ask_mutex);
    student = false;
}

/**
 * The student is satisfied with the answer to his most recent question.
 * print 'Student x is satisfied'.
 * QuestionDone() should not print anything until the professor has finished answering the question.
 */
void QuestionDone(int student_id){
    printf("Student %d is satisfied\n", student_id);
}

/**
 * The professor starts to answer a question of a student.
 * Print 'Professor starts answer question for student x'
 */
void AnswerStart(int student_id){
    printf("Professor starts to answer question for student %d\n", student_id);
}

/**
 * The professor is done answering a question of a student.
 * Print 'Professor is done with answer for student x'
 */
void AnswerDone(int student_id){
    int rand = (random() % 1000) + 1;
    printf("Professor is done with answer for student %d\n", student_id);
    usleep(rand);
}

/**
 * It is the student's turn to enter the professor's office to ask questiosn.
 * print 'Student x shows up in the office'
 */
void EnterOffice(int student_id){
    pthread_mutex_lock(&full_mutex);
    while(occupancy >= capacity){
        pthread_cond_wait(&full_cv, &full_mutex);
    }
    printf("Student %d shows up in the office\n", student_id);
    occupancy++;
    pthread_mutex_unlock(&full_mutex);
}

/**
 * The student has no more questions to ask, so he/she leaves the professor's office
 * print 'Student x leaves the office.'
 */
void LeaveOffice(int student_id){
    pthread_mutex_lock(&full_mutex);
    printf("Student %d leaves the office.\n", student_id);
    occupancy--;
    pthread_cond_signal(&full_cv);
    pthread_mutex_unlock(&full_mutex);
}

/**
 * This function creates a thread that represents a new student with identifier id
 * that asks the professor one or more questions. First, each
 * student need to enter the professor's office by calling EnterOffice().. If the office already
 * full, the student must wait.
 */
void* Student(void* id){
    int id_value = *(int*)id;
    EnterOffice(id_value);
    int questions = (id_value % 4) + 1;
    for(int i = 0;i < questions;i++){
       if(random() > RAND_MAX / 2)
            usleep(500);
        pthread_mutex_lock(&lock4);
        current_student = id_value;
        QuestionStart(id_value);
        QuestionDone(id_value);
        pthread_mutex_unlock(&lock4);
    }
    LeaveOffice(id_value);
    return NULL;
}

/**
 *  This function starts a thread that runs a loop calling AnswerStart()
 *  and AnswerDone(). AnswerStart() blocks when there are no students around
 */
void* Professor(void* ID){
    professor = true;
    while(true){
        pthread_cond_wait(&question_answered_cv, &question_answer_mutex);
        professor = false;
        AnswerStart(current_student);
        AnswerDone(current_student);
        while(student) pthread_cond_signal(&question_asked_cv);
        student = true;

    }
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
    // initializing all variables
    int number_of_students = atoi(argv[1]);
    capacity = atoi(argv[2]);

    // initializing conditional variables
    pthread_cond_init(&question_asked_cv, NULL);
    pthread_cond_init(&question_answered_cv, NULL);
    pthread_cond_init(&full_cv, NULL);

    // initializing mutex locks
    pthread_mutex_init(&question_answer_mutex,NULL);
    pthread_mutex_init(&question_ask_mutex, NULL);
    pthread_mutex_init(&full_mutex, NULL);
    pthread_mutex_init(&lock4, NULL);

    // starting program with creation of professor
    pthread_t professor;
    pthread_create(&professor, NULL, Professor, NULL);
    // populating office hours with students
    pthread_t students[number_of_students];
    int studentIDs[number_of_students];
    // giving each student a unique id
    for(int i = 0;i < number_of_students;i++){
        studentIDs[i] = i;
    }
    // student will now become a student thread
    for(int i = 0;i < number_of_students;i++){
        pthread_create(&students[i], NULL, Student, (void *) &studentIDs[i]);
    }
    // wait for all students to finish
    for(int i = 0;i < number_of_students;i++){
        pthread_join(students[i], NULL);
    }
    // deleting mutexes
    pthread_mutex_destroy(&full_mutex);
    pthread_mutex_destroy(&question_ask_mutex);
    pthread_mutex_destroy(&question_answer_mutex);
    pthread_mutex_destroy(&lock4);

    // deleting conditional variables
    pthread_cond_destroy(&question_asked_cv);
    pthread_cond_destroy(&full_cv);
    pthread_cond_destroy(&question_answered_cv);
    return 0;
}
