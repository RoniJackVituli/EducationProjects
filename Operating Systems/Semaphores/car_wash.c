/*  Created by Roni Jack Vituli on 07/05/2022.
    
 Authors -> Roni Jack Vituli - 315369967
 
 Mission HW4 Operating System.
 
 */


/*Libary*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <signal.h>
#include <math.h>
#define SEMPERM 0600
#define True 1
#define False 0
#define NO_ERORR 0
#define SIZE 40
typedef union _semun{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
}semun;


typedef struct{
    int total_car_wash;
    double correct_time;
    double total_time;
    double pid_time;
}Queue;


int PROGRAM = True;

int SEMID_CAR = -1;
int SEMID_WASH = -1;
key_t CAR_KEY, WASH_KEY;
float* TOTAL_TIMME = NULL;
float nextTime(float rateParameter);
void input_washing_machine(int* wm);
void finish_the_program(int sig);


int initsems(int);
void free_sems(void);
int p(int semid);
int v(int semid);
void handlesem(Queue*);
void wash_car(Queue*);




int main(int argc, const char * argv[]) {
    int total_wash_machine = 0;
    input_washing_machine(&total_wash_machine);
    int status  = 0;

    /*Create Semaphore for Queue and Wash Mechine*/
    if(!initsems(total_wash_machine)){
        printf("fail\n");
        exit(EXIT_FAILURE);
    }
    
    /*Create Share memory for queue!*/
    key_t key = ftok(".", 87987987);
    int queue_shmid;
    if( ( queue_shmid = shmget(key, sizeof(Queue),  SEMPERM | IPC_CREAT | IPC_EXCL ) ) == -1 )
        if( errno == EEXIST )
            queue_shmid = semget(key, 1, 0 );
    Queue* queue = (Queue*)shmat(queue_shmid, 0, 0);
   
    queue->total_car_wash = 0;
    queue->total_time = nextTime(1.0/(total_wash_machine*5));
    queue->correct_time = 0.0; 
    queue->pid_time = 0.0;
    
//
   key_t time_key = ftok(".", 14020);
   int time_shmid;
   if( ( time_shmid = shmget(time_key, sizeof(float),  SEMPERM | IPC_CREAT | IPC_EXCL ) ) == -1 )
       if( errno == EEXIST )
           time_shmid = semget(time_key, 1, 0 );
   float* time = (float*)shmat(time_shmid, 0, 0);
   TOTAL_TIMME = time;
    
   printf("total time = %lf\n",queue->total_time);
//    queue->correct_time =  nextTime(1.0 / ((total_wash_machine + 1) / 2));
   while(queue->correct_time < queue->total_time && PROGRAM){
       if(fork() == 0){
           p(SEMID_CAR);
           signal(SIGINT,finish_the_program);
           queue->correct_time += nextTime(1.0 / ((total_wash_machine + 1) / 2));
           v(SEMID_CAR);
           srand(getpid());
           handlesem(queue);
           wash_car(queue);
       }else{
            sleep(nextTime(1.0 / ((total_wash_machine + 1) / 2)));
            // queue->correct_time += nextTime(1.0 / ((total_wash_machine + 1) / 2));

       }
   }
    // printf("heey\n");
    //  while(correct_time < total_time){
    //      printf("heey\n");
    //     if(fork() == 0){
    //         srand(getpid());
    //         handlesem(queue);
    //         wash_car(queue);
    //     }else{
    //         sleep(nextTime(1.0 / ((total_wash_machine + 1) / 2)));
    //         correct_time += nextTime(1.0/1.0/3.0);
    //         printf("correct_time = %lf\n",correct_time);
    //     }
    // }

    while(wait(&status) > 0);

    printf("Time Taken %.5lf seconds, car washed = %d\n",queue->correct_time ,queue->total_car_wash);
    shmctl(queue_shmid, IPC_RMID, 0);
    free_sems();
    exit(EXIT_SUCCESS);
}



void handlesem(Queue* queue){
    p(SEMID_CAR);
    queue->pid_time = queue->correct_time;
    printf("Car : %d , Arrive! at Time %.5f\n",getpid(),queue->pid_time);
    sleep(((float)rand()/(float)(RAND_MAX)) * 2.0);
    v(SEMID_CAR);
}


void wash_car(Queue* queue){
    
    p(SEMID_WASH);
    printf("Car : %d , in the washing machine! , Time %.5f\n",getpid(),queue->pid_time);
    float t = ((float)rand()/(float)(RAND_MAX))* 5.0; 
    sleep(t);
    queue->pid_time = queue->correct_time + t;
    printf("Car : %d , leave the washine machine! , Time %.5f\n",getpid(), queue->pid_time);
    queue->total_car_wash += 1;
    v(SEMID_WASH);
    queue->correct_time += t;
    exit(EXIT_SUCCESS);
}




int p(int semid){
  struct sembuf p_buf;
  p_buf.sem_num = 0;
  p_buf.sem_op = -1;
  p_buf.sem_flg = SEM_UNDO;

    //int semop(int semid, struct sembuf *sops, size_t nsops);
  if( semop(semid, &p_buf, 1) == -1 ){
    perror("Error operation p(semid)");
    exit(1);
  }
  return 0;
}

int v(int semid){
  struct sembuf v_buf;
  v_buf.sem_num = 0;
  v_buf.sem_op = 1;
  v_buf.sem_flg = SEM_UNDO;

//int semop(int semid, struct sembuf *sops, size_t nsops);
  if( semop(semid, &v_buf, 1) == -1 ){
    perror("Error operation v(semid)");
    exit(1);
  }
  return 0;
}








float nextTime(float rateParameter){
    return -logf(1.0f - (float)rand() / ((double)RAND_MAX + 1)) / rateParameter;
}




int initsems(int total_wash_machine){
    CAR_KEY = ftok(".", 1);
    WASH_KEY = ftok(".",2);
    union _semun arg;
    int status = 0;
    
    if( ( SEMID_CAR = semget(CAR_KEY, 1, SEMPERM | IPC_CREAT | IPC_EXCL ) ) == -1 )
        if( errno == EEXIST )
            SEMID_CAR = semget(CAR_KEY, 1, 0 );
   

    arg.val = 1;
    status = semctl(SEMID_CAR, 0, SETVAL, arg);
    
    
    if( SEMID_CAR == -1 || status == -1 ){
        perror("Error initsem car");
        return False;
    }
    
    
    if( ( SEMID_WASH = semget(WASH_KEY, 1, SEMPERM | IPC_CREAT | IPC_EXCL ) ) == -1 )
        if( errno == EEXIST )
            SEMID_WASH = semget(WASH_KEY, 1, 0 );
    
    arg.val = total_wash_machine;
    status = semctl(SEMID_WASH, 0, SETVAL, arg);
    
    if( SEMID_CAR == -1 || status == -1 ){
        perror("Error initsem wash");
        return False;
    }
    return True;
}


void free_sems(void){
    semctl(CAR_KEY, 0, IPC_RMID, NULL);
    semctl(WASH_KEY, 0, IPC_RMID, NULL);
}





void input_washing_machine(int* wm){
    do{
        signal(SIGINT,finish_the_program);
        if(*wm > 5 || *wm < 0){
            printf("\n\n--------------ERROR------------\n");
            printf("Please Enter number between 1 - 5");
            printf("\n--------------ERROR------------\n\n");
        }else if(!PROGRAM){
            printf("Thank You & Good Bye! (Press ctl-c)\n");
            exit(EXIT_SUCCESS);
        }
        printf("How many wash machine do you want in your program?\n");
        scanf("%d",wm);
    }while(*wm > 5 || *wm < 0);
}

void finish_the_program(int sig){
    PROGRAM = 0;
    return;
}
