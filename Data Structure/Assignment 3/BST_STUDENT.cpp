#include "BST_STUDENT.h"

StudentNode* create_new_student(int id){
    /*
     This function get ID and create new Node of student.
     */
    StudentNode* new_Student = (StudentNode*)malloc(sizeof(StudentNode));
    new_Student->ID = id;
    new_Student->grade_final_test = ZERO;
    new_Student->grade_mid_test = ZERO;
    new_Student->left = NULL;
    new_Student->Right = NULL;
    new_Student->Parent = NULL;
    return new_Student;
}

int Search(BST* tree,int id){
    /*
     fuction search find student in the tree.
     */
    return binSearch(tree->root, id);
}

int binSearch(StudentNode* node,int id){
    /*
     check if the student on the tree.
     */
    if(node == NULL)
        return False;
    if(node->ID == id)
        return True;
    if (node->ID <= id)
        return binSearch(node->Right, id);
    else
        return binSearch(node->left, id);
}

void insert(BST* tree, int ID){
    /*
     this function add a new student in the tree.
     */
    StudentNode* newStudent = create_new_student(ID);
    if((Search(tree, ID))){
        printf("The Student %d is in the tree\n",ID);
        free(newStudent);
    }else{
        StudentNode* y = NULL;
        StudentNode* x = tree->root;
        while (x != NULL) {
            y = x;
            if(newStudent->ID < x->ID)
                x = x->left;
            else
                x = x->Right;
        }
        newStudent->Parent = y;
        if(y == NULL)
            tree->root = newStudent;
        else if(newStudent->ID < y->ID)
            y->left = newStudent;
        else
            y->Right = newStudent;
    }
}

void updateMidtermGrade(BST* tree, int ID, int newGrade){
    /*
     this function updata the mid exam grade.
     */
    StudentNode* Node = correct_node(tree->root, ID);
    if(Node != NULL)
        Node->grade_mid_test = newGrade;
}


void updateExamGrade(BST* tree, int ID, int newGrade){
    /*
     this function update the Test grade.
     */
    StudentNode* Node = correct_node(tree->root, ID);
    if(Node != NULL)
        Node->grade_final_test = newGrade;
}


StudentNode* correct_node(StudentNode* Node, int ID){
    /*
     this function return me the correct node that i search.
     */
    if(Node == NULL)
        return NULL;
    if(Node->ID == ID)
        return Node;
    if (Node->ID <= ID)
        return correct_node(Node->Right, ID);
    else
        return correct_node(Node->left, ID);
}

int getFinalGrade(BST* tree, int ID){
    /*
     this function calculate the final Grade.
     */
    float FinalGrade = ZERO;
    StudentNode* Node = correct_node(tree->root, ID);
    if(Node != NULL){
        FinalGrade = (Node->grade_final_test*WEDIHT_FINAL_GRADE) + (Node->grade_mid_test*WEDIHT_MID_GRADE);
        return RoundNumber(FinalGrade);
    }
    return ZERO;
}

int RoundNumber(float num){
    /*
     this function round number if the number is 38.2 so he return 38 if the number is 38.7 he return 39
     */
    int tempCheck, roundNum, tempNum;
    tempNum = (int)(num*10);
    tempCheck = tempNum%10;
    if(tempCheck>=5){
        roundNum = (int)num;
        roundNum++;
    }else{
        roundNum = (int)num;
    }
    return roundNum;
}

double getAverageGrade(BST* tree){
    /*
     this function return the average of all the grades in the tree.
     */
    if(tree == NULL)
        return ZERO;
    int countNode = countNodes(tree->root);
    double sum = sum_of_all_grades(tree->root);
    return (double)(sum/countNode);
}

int sum_of_all_grades(StudentNode* Node){
    /*
     this function return the sum of all the grades.
     */
    if(Node == NULL)
        return ZERO;
    return Node->grade_final_test + sum_of_all_grades(Node->left) + sum_of_all_grades(Node->Right);
}

int countNodes(StudentNode* Node){
    /*
     this function how many nodes i have in the tree
     */
    if(Node == NULL)
        return ZERO;
    return 1 + countNodes(Node->Right) + countNodes(Node->left);
}

void reportGrades(BST* tree){
    PrintStudent(tree->root);
}

void PrintStudent(StudentNode* Node){
    /*
     this function Print the info of student.
     */
    if(Node == NULL)
        return;
    PrintStudent(Node->left);
    printf("ID: %d\tExam: %d\tTest: %d\tFinal Grade: %d\n",Node->ID, Node->grade_mid_test,Node->grade_final_test, get_final_grade(Node));
    PrintStudent(Node->Right);
}


int get_final_grade(StudentNode* Node){
    float FinalGrade = ZERO;
    FinalGrade = (Node->grade_final_test*WEDIHT_FINAL_GRADE) + (Node->grade_mid_test*WEDIHT_MID_GRADE);
    return RoundNumber(FinalGrade);
}

int getNumOfFails(BST* tree){
    return FAIL(tree->root);
}

int FAIL(StudentNode* Node){
    /*
     this function count how many student are fail in the course.
     */
    if(Node == NULL)
        return 0;
    if(get_final_grade(Node) < 56)
        return 1 + FAIL(Node->left) + FAIL(Node->Right);
    else
        return FAIL(Node->left) + FAIL(Node->Right);
}

void ReportsStatistics(BST* tree){
    /*
     this function print the statistics of the course.
     */
    int good = GOOD(tree->root), Very_Good = very_good(tree->root), excellent = Excellent(tree->root);
    printf("Good\t(56-75)\t%d\n\nVery good\t(76-94)\t%d\n\nExcellent\t(95-100)\t%d\n\n",good,Very_Good,excellent);
}

int GOOD(StudentNode* Node){
    /*
     this function count how many student have final garde betwenn 56 - 75
     */
    if(Node == NULL)
        return 0;
    if(get_final_grade(Node) >= 56 && get_final_grade(Node) <= 75)
        return 1  + GOOD(Node->left) + GOOD(Node->Right);
    else
        return GOOD(Node->left) + GOOD(Node->Right);
}

int very_good(StudentNode* Node){
    /*
     this function count how many student have final garde betwenn 76 - 94
     */
    if(Node == NULL)
        return 0;
    if(get_final_grade(Node) >= 76 && get_final_grade(Node) <= 94)
        return 1  + very_good(Node->left) + very_good(Node->Right);
    else
        return very_good(Node->left) + very_good(Node->Right);
}

int Excellent(StudentNode* Node){
    /*
     this function count how many student have final garde betwenn 95 - 100
     */
    if(Node == NULL)
        return 0;
    if(get_final_grade(Node) >= 95 && get_final_grade(Node) <= 100)
        return 1  + Excellent(Node->left) + Excellent(Node->Right);
    else
        return Excellent(Node->left) + Excellent(Node->Right);
}

void FreeTree(BST* tree){
    /*
     this function free the tree
     */
    FreeNode(tree->root);
}

void FreeNode(StudentNode* Node){
    /*
     this function free the node
     */
    if(Node == NULL)
        return;
    FreeNode(Node->left);
    FreeNode(Node->Right);
    free(Node);
}

int checkGrades(int* grade){
    /*
     this function check if the grade the user enter is ok.
     */
    while(!(*grade >= 0 && *grade <= 100)){
        printf("The grade %d is not correct!\nPlease enter new grade between 0 - 100\n",*grade);
        scanf("%d",grade);
    }
    return *grade;
}
