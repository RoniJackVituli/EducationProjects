//Part2
//Campus:Beer Sheva
//Author: Roni Jack Vituli ID:315369967.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define NO_ERROR 0
typedef struct {
    char* courseName;
    int grade;
} Course;
typedef struct {
    char* studentName;
    Course* course_arr;
    int size;
}Student;
void InputCourse(Course* pCourse);
void PrintCourse(Course Cours);
void InputStudent(Student* pSt);
void PrintStudent(Student st);
void CourseList(Student* arrSt, int size, char* CourseName);
void PrintAll(Student* pSt, int size);
void FreeAll(Student** pSt, int size);
int Build(Student** pSt);
int main(){
    Student* pSt=NULL;
    int size;
    size=Build(&pSt);
    PrintAll(pSt, size);
    CourseList(pSt,size, "Matlab");
    FreeAll(&pSt, size);
    return NO_ERROR;
}
//The inputCours function inserts data for one student per course
void InputCourse(Course* pCourse){
    char buffer[MAX];
    printf("Enter The name of the course\n");
    scanf("%[^\n]s",buffer);
    pCourse->courseName=(char*)malloc(strlen(buffer)*(sizeof(char)));
    strcpy(pCourse->courseName, buffer);
    printf("What is the grade of the course?\n");
    scanf("%d",&(*pCourse).grade);
}
//The PrintCourse function prints data for one course per student on the screen.
void PrintCourse(Course Cours){
    printf("The name of the course is: %s",Cours.courseName);
    printf("The Grade of the course is: %d\n",Cours.grade);
}
//The inputStudent function captures data for one student, including data on the student's courses
void InputStudent(Student* pSt){
    getchar();
    char buffer[MAX];
    printf("What is your name?\n");
    fgets(buffer, MAX, stdin);
    pSt->studentName=(char*)malloc(strlen(buffer)*sizeof(char));
    strcpy(pSt->studentName, buffer);
    printf("How many courses do you have?\n");
    scanf("%d",&(*pSt).size);
    getchar();
    pSt->course_arr=(Course*)malloc(pSt->size*sizeof(Course));
    for (int i=0; i < (*pSt).size ; i++) {
        InputCourse(&pSt->course_arr[i]);
        getchar();
    }
    
}
//The PrintStudent function prints data for one student from the screen, including data on the student's courses.
void PrintStudent(Student st){
    printf("Your name: %s",st.studentName);
    for (int i=0; i<st.size; i++) {
        PrintCourse(st.course_arr[i]);
    }
}
//The Build function creates and initializes a set of Student-type structures using user input. It returns the array (through the pointer) and its size.
int Build(Student** pSt){
    int size;
    printf("How many Students?\n");
    scanf("%d",&size);
    *pSt=(Student*)malloc(size*sizeof(Student));
    for (int i=0; i<size; i++)
        InputStudent(&(*pSt)[i]);
    return size;
}
//The FreeAll function frees all the allocated dynamic memory.
void FreeAll(Student** pSt, int size){
    for (int i=0; i<size; i++) {
        for(int j=0; j<(*pSt)[i].size;j++)
            free((*pSt)[i].course_arr[j].courseName);
        free((*pSt)[i].course_arr);
    }
    free(*pSt);
}
//The PrintAll function prints all the details of the stadadont, including details of the courses they have taken.
void PrintAll(Student* pSt, int size){
    for (int i=0; i<size; i++) {
        printf("%s",pSt[i].studentName);
        for (int j=0; j<pSt[i].size; j++) {
            printf("Coures: %s\n",pSt[i].course_arr[j].courseName);
            printf("Grade: %d\n",pSt[i].course_arr[j].grade);
        }
    }
}
//The PrintAll function accepts student parameters and their size as well as the course name. The function prints the names of all students who have passed this course (their grade in the course is at least 56.)
void CourseList(Student* pSt, int size, char* CourseName){
    printf("The Students are pass the Cours: %s are:\n",CourseName);
    for (int i=0; i<size; i++) {
        for(int j=0; j<pSt[i].size ; j++){
            if (!strcmp(pSt[i].course_arr[j].courseName, CourseName) && pSt[i].course_arr[j].grade>=56) {
                printf("%s",pSt[i].studentName);
            }
        }
    }
}




