#include "BST_STUDENT.cpp"

int main() {
    int exam_grade, final_grade;
    BST* Tree = (BST*)malloc(sizeof(BST));
    Tree->root = NULL;
    int *arr ,size = 0;
    printf("How many student you want?\n");
    scanf("%d",&size);
    arr = (int*)malloc(size*sizeof(int));
    if(arr == NULL){
        printf("No memory\n");
        exit(1);
    }
    printf("Enter the ID of %d Students\n",size);
    for(int i = 0 ; i < size ; i++){
        scanf("%d",&arr[i]);
        insert(Tree, arr[i]);
    }
    printf("Enter the grades of the exam and the final test for each student\n");
    for (int i = 0 ; i < size ; i++) {
        printf("Student Number %d ID: %d\n",i+1,arr[i]);
        scanf("%d%d",&exam_grade,&final_grade);
        updateMidtermGrade(Tree, arr[i], checkGrades(&exam_grade));
        updateExamGrade(Tree, arr[i], checkGrades(&final_grade));
    }
    reportGrades(Tree);
    printf("\nThe amount of faild is: %d\n\n", getNumOfFails(Tree));
    ReportsStatistics(Tree);
    FreeTree(Tree);
    free(arr);
    return NO_ERROR;

}
