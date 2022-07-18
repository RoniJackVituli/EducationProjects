#ifndef BST_STUDENT_h
#define BST_STUDENT_h

#include <stdio.h>
#include <stdlib.h>

#define WEDIHT_MID_GRADE 0.3
#define WEDIHT_FINAL_GRADE 0.7
#define ZERO 0
#define NO_ERROR 0

typedef enum {False,True} BOOL;
typedef struct StudentNode{
    int ID;
    int grade_mid_test = ZERO;
    int grade_final_test = ZERO;
    StudentNode* left;
    StudentNode* Right;
    StudentNode* Parent;
    
} StudentNode;

typedef struct BST{
    StudentNode *root;
} BST;

void insert(BST* tree, int ID);
void updateMidtermGrade(BST* tree, int ID, int newGrade);
void updateExamGrade(BST* tree, int ID, int newGrade);
int getFinalGrade(BST* tree, int ID);
double getAverageGrade(BST* tree);
void reportGrades(BST* tree);
int getNumOfFails(BST* tree);
void ReportsStatistics(BST* tree);


//My functions
void PrintStudent(StudentNode* Node);
int Search(BST* tree, int ID);
int binSearch(StudentNode* Node, int ID);
int get_final_grade(StudentNode* Node);
StudentNode* create_new_student(int id);
StudentNode* correct_node(StudentNode* Node, int id);
int sum_of_all_grades(StudentNode* Node);
int RoundNumber(float);
int countNodes(StudentNode* Node);
int FAIL(StudentNode* Node);
int GOOD(StudentNode* Node);
int very_good(StudentNode* Node);
int Excellent(StudentNode* Node);
void FreeTree(BST* tree);
void FreeNode(StudentNode* Node);

int checkGrades(int* Grade);
#endif /* BST_STUDENT_hpp */
