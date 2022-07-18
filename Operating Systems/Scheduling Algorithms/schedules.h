//
//  schedules.h
//  HW3
//
//  Created by Roni Jack Vituli on 25/04/2022.
//

#ifndef schedules_h
#define schedules_h
#define MAX 10
#define COMMA ","
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {False=0,True=1} BOOL;

enum Algoritm {
    First_Come_First_Served = 1,
    Shortest_Job_First = 2,
    HRRN = 3,
    Round_Robin = 4,
    Priority_With_Round_Robin = 5
};

typedef struct{
    int task_id;
    int priority;
    int arrival_time;
    int burst_time;
    int status;
}Task;



void FCFS(Task*, int);
void SJF(Task*, int);
void RoundRobin(Task*, int);
void Highest_Response_Ratio_Next(Task*, int);
void RoundRobinWithPriorty(Task*, int);
void print_tasks(Task*, int size);

Task* moveOneStepLeft(Task* queue, int size);
void finishTheTask(Task* tasks,int size,Task task);
void Display(Task*, int size);
void Schedule(Task*,int);
Task* Table(Task*,int*,Task);
Task Build(char* buffer);
void swap(Task* xp, Task* yp);
void BubbleSort_Arrival_Time(Task*, int size);
void BubbleSort_Burst_Time(Task*, int size);
Task* CopyTasks(void);

/* My Functions*/
void sort_by_priortiy(Task* ,int);
void start(const char*);
char* split_comma(char* buffer);
int casting_charNum_to_int(char);
void set_status(Task*,int);
void check_is_there_same_burst(Task*,int);
int queue_has_element(Task*,int size,Task);
Task* deleteElement(Task*, int size);
void checkPrint(Task* temp, int size);
int sum_of_burst_time(Task*,int);
Task* cpy(Task*, int);
#endif /* schedules_h */
