//
//  main.c
//  HW3
//
//  Created by Roni Jack Vituli on 25/04/2022.
//

#include "schedules.h"

int main(int argc, const char * argv[]) {
    start(argv[1]);
    return 0;
}

/* ###################################################################### */


void start(const char* str){
    FILE* fptr = fopen(str, "r");
    Task task;
    if(fptr == NULL){
        printf("can't open the file %s\n",str);
        printf("please enter the path of the file.\n");
        exit(1);
    }
    Task* tasks = (Task*)malloc(sizeof(Task*));
    int size = 1;
    if(tasks == NULL){
        printf("no memory allocated! (tasks - Start function)\n");
        fclose(fptr);
        exit(1);
    }

    char buffer[MAX];
    while(fgets(buffer, MAX, fptr) != NULL){
        task = Build(buffer);
        tasks = Table(tasks,&size,task);
    }
    tasks = realloc(tasks, sizeof(Task)*((size--)));
    fclose(fptr);
    Display(tasks, size);
    Schedule(tasks,size);

}


Task* Table(Task* tasks, int* size, Task task){
    tasks[(*size)-1] = task;
    tasks = realloc(tasks, sizeof(Task)*((*size) + 1));
    *size += 1;
    return tasks;
}





Task Build(char* buffer){
    char* temp = split_comma(buffer);
    Task task;
    task.task_id = casting_charNum_to_int(temp[0]);
    task.priority =  casting_charNum_to_int(temp[1]);
    task.arrival_time =  casting_charNum_to_int(temp[2]);
    task.burst_time =  casting_charNum_to_int(temp[3]);
    task.status = 0;
    return task;
}


char* split_comma(char* buffer){
    char* temp = strtok(buffer, COMMA);
    char* newTemp = (char*)malloc(sizeof(char));
    if(newTemp == NULL){
        printf("no memory allocated for newTemp.\n");
        exit(1);
    }
    int index = 0;
    while(temp != NULL){
        newTemp[index++] = *temp;
        newTemp = realloc(newTemp, ((index-1) + 1) * sizeof(char));
        temp = strtok(NULL, COMMA);
    }
    return newTemp;
}

int casting_charNum_to_int(char ch){
    if(ch >= '0' && ch <= '9'){
        return (int)(ch - '0');
    }else{
        printf("this char %c is incorrent input!\n",ch);
        exit(1);
    }
}

void Display(Task* tasks, int size){
    printf("\n\n-----------PROCESS TABLE----------------\n\n");
    printf("ID\t|Priority\t|Arrival Time\t|Burst Time\n");
    for (int i = 0; i < size; i++) {
        printf("----------------------------------------------\n");
        printf("%d\t|%-10d\t|%-10d\t\t|%-10d\n",tasks[i].task_id, tasks[i].priority, tasks[i].arrival_time, tasks[i].burst_time);
    }
}
Task* cpy(Task* tasks, int size){
    Task* temp = (Task*)malloc(sizeof(Task)*size);
    for (int i = 0 ; i < size; i++) {
        temp[i] = tasks[i];
    }
    return temp;
}
void Schedule(Task* tasks, int size){
    Task* temp = cpy(tasks,size);
    FCFS(tasks, size);
    SJF(tasks,size);
    Highest_Response_Ratio_Next(tasks,size); // HRRN
    RoundRobin(temp,size);
    RoundRobinWithPriorty(temp,size);
    free(temp);
}


void FCFS(Task* tasks, int size){
    BubbleSort_Arrival_Time(tasks,size);
    printf("\n\n---------------FCFS Algo-------------------\n\n");
    print_tasks(tasks,size);
}


void BubbleSort_Arrival_Time(Task* tasks, int size){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size - 1 - i; j++)
            if (tasks[j].arrival_time > tasks[j + 1].arrival_time)
                swap(&tasks[j], &tasks[j + 1]);
            else if(tasks[j].arrival_time == tasks[j + 1].arrival_time)
                if (tasks[j].task_id > tasks[j + 1].task_id)
                    swap(&tasks[j], &tasks[j + 1]);
}
void BubbleSort_Burst_Time(Task* tasks, int size){
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size - 1 - i; j++)
            if (tasks[j].burst_time > tasks[j + 1].burst_time)
                swap(&tasks[j], &tasks[j + 1]);
            else if(tasks[j].burst_time == tasks[j+1].burst_time)
                swap(&tasks[j], &tasks[j + 1]);
}

void swap(Task* xp, Task* yp){
    Task temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void SJF(Task* tasks, int size){
    printf("\n\n---------------SJF Algo-------------------\n\n");
    BubbleSort_Arrival_Time(tasks,size);
    Task* finish_tasks = (Task*)malloc(sizeof(Task)*size);
    Task* Queue = (Task*)malloc(sizeof(Task));
    int size_of_queue = 1, k = 0;
    int sum_bt = sum_of_burst_time(tasks,size);
    
    finish_tasks[k++] = tasks[0];
    tasks[0].status = 1;
    for (int total = tasks[0].burst_time; total < sum_bt;) {
        for (int i = 0; i < size; i++) {
            if(tasks[i].arrival_time <= total && tasks[i].status != 1 && !queue_has_element(Queue, size_of_queue, tasks[i])){
                Queue = realloc(Queue, sizeof(Task)*(size_of_queue + 1));
                Queue[size_of_queue-1] = tasks[i];
                size_of_queue++;
            }
        }
        BubbleSort_Burst_Time(Queue, size_of_queue - 1);
        check_is_there_same_burst(Queue, size_of_queue - 1);
            
        for (int i = 0; i < size; i++) {
            if(tasks[i].status != 1 && tasks[i].task_id == Queue[0].task_id){
                tasks[i].status = 1;
                total += tasks[i].burst_time;
                finish_tasks[k++] =  tasks[i];
                break;
            }
        }
        if (size_of_queue > 0) {
            Queue = deleteElement(Queue, --size_of_queue);
        }
    }
    free(Queue);
    print_tasks(finish_tasks,size);
    free(finish_tasks);

}
int queue_has_element(Task* tasks ,int size,Task task){
    for (int i = 0; i < size; i++) {
        if(tasks[i].task_id == task.task_id)
            return 1;
    }
    return 0;
}
void check_is_there_same_burst(Task* arr,int size){
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i].burst_time == arr[j].burst_time) {
                swap(&arr[i], &arr[j]);
                return;
            }
        }
    }
}

Task* deleteElement(Task* arr, int size){
    Task temp;
    for (int i = 0; i < size/2; i++) {
        temp = arr[i];
        arr[i] = arr[size-i-1];
        arr[size-i-1] = temp;
    }
    arr = realloc(arr, sizeof(Task)*(size-1));
    return arr;
}

               


int sum_of_burst_time(Task* tasks, int size){
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += tasks[i].burst_time;
    }
    return sum;
}





void checkPrint(Task* temp, int size){
    for (int i = 0 ; i < size; i++) {
        printf("<P%d,%d> ",temp[i].task_id , temp[i].burst_time);
    }
    printf("\n");

}


void print_tasks(Task* tasks, int size){
    for (int i = 0 ; i < size; i++) {
        printf("<P%d,%d> ",tasks[i].task_id , tasks[i].burst_time);
    }
    printf("\n");
}


void Highest_Response_Ratio_Next(Task* tasks, int size){
    BubbleSort_Arrival_Time(tasks,size);
    set_status(tasks,size);
    float ratio;
    float hrr;
    int loc = 0;
    int sum_bt = sum_of_burst_time(tasks,size);
    Task* temp = (Task*)malloc(sizeof(Task)*size);

    for (int t = tasks[0].arrival_time, k = 0 ; t < sum_bt ;) {
        hrr = -999;
        for (int i = 0; i < size; i++) {
            if(tasks[i].arrival_time <= t && tasks[i].status != 1){
                ratio = (tasks[i].burst_time + (t - tasks[i].arrival_time))/tasks[i].burst_time;
                if (hrr < ratio){
                    hrr = ratio;
                    loc = i;
                }
            }
        }
        t += tasks[loc].burst_time;
        tasks[loc].status = 1;
        temp[k++] = tasks[loc];
    }
    free(tasks);
    tasks = NULL;
    tasks = temp;
    printf("\n\n---------------HRRN Algo-------------------\n\n");
    print_tasks(tasks,size);
}


void set_status(Task* tasks,int size){
    for(int i = 0 ; i < size; i++)
        tasks[i].status = 0;
}


void RoundRobin(Task* tasks, int size){
    printf("\n\n---------------Round Robin Algo-------------------\n\n");
    set_status(tasks, size);
    BubbleSort_Arrival_Time(tasks, size);
    int count = 0;
    int flag = 0;
    int const quantum = 2;
    int total = 0;
    Task* Queue = (Task*)malloc(sizeof(Task));
    int size_queue = 1;
    Queue[0] = tasks[0];
    while(True){
        for (int i = 0; i < size; i++) {
            flag = 0;
            if(tasks[i].status == 1)
                continue;
            if (Queue[0].burst_time > quantum) {
                Queue[0].burst_time -= quantum;
                total += quantum;
                flag = 1;
                printf("<P%d,%d> ",Queue[0].task_id , quantum);
                for (int j = i; j < size; j++) {
                    if (tasks[j].arrival_time <= total && tasks[j].status != 1 && !queue_has_element(Queue, size_queue, tasks[j])) {
                        Queue = realloc(Queue, sizeof(Task)*(size_queue + 1));
                        size_queue++;
                        Queue[size_queue-1] = tasks[j];
                    }
                }
            }else if(Queue[0].burst_time <= quantum){
                printf("<P%d,%d> ",Queue[0].task_id , Queue[0].burst_time);
                for (int j = i; j < size; j++) {
                    if (tasks[j].arrival_time <= total && tasks[j].status != 1 && !queue_has_element(Queue, size_queue, tasks[j])) {
                        Queue = realloc(Queue, sizeof(Task)*(size_queue + 1));
                        size_queue++;
                        Queue[size_queue-1] = tasks[j];
                    }
                }
                total += Queue[0].burst_time;
                Queue[0].burst_time = 0;
                finishTheTask(tasks, size, Queue[0]);
                count++;
            }
            if (flag) {
                Queue = moveOneStepLeft(Queue,size_queue);
            }else if(size_queue > 0){
                Queue = moveOneStepLeft(Queue,size_queue);
                Queue = realloc(Queue, sizeof(Task)*(size_queue-1));
                --size_queue;
            }else if(count == size)
                break;
        }
        if(count == size)
           break;
    }
    free(Queue);
    printf("\n");
}

Task* moveOneStepLeft(Task* queue, int size){
    Task* temp = (Task*)malloc(sizeof(Task)*size);
    for (int i = 0, j = 0; j < size; j++) {
        if(j == 0)
            temp[size-1] = queue[j];
        else
            temp[i++] = queue[j];
    }
    free(queue);
    return temp;
}

void finishTheTask(Task* tasks,int size,Task task){
    for (int i = 0 ; i < size; i++) {
        if (tasks[i].task_id == task.task_id) {
            tasks[i].status = 1;
            return;
        }
    }
}

void RoundRobinWithPriorty(Task* tasks, int size){
    printf("\n\n---------------Round Robin With Priority Algo-------------------\n\n");
    set_status(tasks, size);
    BubbleSort_Arrival_Time(tasks, size);
    int count = 0;
    int flag = 0;
    int const quantum = 2;
    int total = 0;
    Task* Queue = (Task*)malloc(sizeof(Task));
    int size_queue = 1;
    Queue[0] = tasks[0];
    while(True){
        for (int i = 0; i < size; i++) {
            flag = 0;
            if(tasks[i].status == 1)
                continue;
            if (Queue[0].burst_time > quantum) {
                Queue[0].burst_time -= quantum;
                total += quantum;
                flag = 1;
                printf("<P%d,%d> ",Queue[0].task_id , quantum);
                for (int j = i; j < size; j++) {
                    if (tasks[j].arrival_time <= total && tasks[j].status != 1 && !queue_has_element(Queue, size_queue, tasks[j])) {
                        Queue = realloc(Queue, sizeof(Task)*(size_queue + 1));
                        size_queue++;
                        Queue[size_queue-1] = tasks[j];
                    }
                }
            }else if(Queue[0].burst_time <= quantum){
                printf("<P%d,%d> ",Queue[0].task_id , Queue[0].burst_time);
                for (int j = i; j < size; j++) {
                    if (tasks[j].arrival_time <= total && tasks[j].status != 1 && !queue_has_element(Queue, size_queue, tasks[j])) {
                        Queue = realloc(Queue, sizeof(Task)*(size_queue + 1));
                        size_queue++;
                        Queue[size_queue-1] = tasks[j];
                    }
                }
                total += Queue[0].burst_time;
                Queue[0].burst_time = 0;
                finishTheTask(tasks, size, Queue[0]);
                count++;
            }
            if (flag) {
                Queue = moveOneStepLeft(Queue,size_queue);
                BubbleSort_Arrival_Time(Queue, size_queue);
                sort_by_priortiy(Queue, size_queue);
            }else if(size_queue > 0){
                Queue = moveOneStepLeft(Queue,size_queue);
                Queue = realloc(Queue, sizeof(Task)*(size_queue-1));
                --size_queue;
                BubbleSort_Arrival_Time(Queue, size_queue);
                sort_by_priortiy(Queue, size_queue);
            }else if(count == size)
                break;
        }
        if(count == size)
           break;
    }
    free(Queue);
    printf("\n");
}

void sort_by_priortiy(Task* tasks ,int size){
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (tasks[j].priority < tasks[j + 1].priority)
                swap(&tasks[j], &tasks[j + 1]);
}

