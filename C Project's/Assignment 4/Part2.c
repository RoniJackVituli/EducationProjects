//Part2.c
//  Created by Roni Jack Vituli ID 31536996;
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NO_ERROR 0
//Declaration of functions
void BuildMatrix(int*** matrix,int row ,int column);
void FreeMatrix(int*** matrix,int row);
void PrintMatrix(int** matrix ,int row,int colum);
int** SubMatrix(int** matrix ,int sizeMatrix, int*pSizeMatrix);
int SumSubMatrix(int** matrix,int indexRow,int indexCol, int* sizeMatrix,int* counter,int size);


//The main program, which input row and column,and if you want creates a square matrix you need to put the same row and column, after he send them to the functions and returns the square sub-matrix whose maximum sum is the maximum, prints it and finally releases all memory.
int main() {
    int **matrix=NULL, row,column;
    printf("Enter Row and Column\n");
    scanf("%d%d",&row,&column);
    BuildMatrix(&matrix, row, column);
    FreeMatrix(&matrix, row);
    return NO_ERROR;
}

//The function gets a pointer to a dynamic 2D array, the number of rows, and the number of columns. The function allocates memory accordingly and fills the matrix with values.
void BuildMatrix(int*** matrix,int row,int column){
    int sizeMatrix;
    int** subMat=NULL;
    int* pSizeMatrix;
    pSizeMatrix=&sizeMatrix;
    *matrix=(int**)malloc(row*sizeof(int*));
    if (*matrix==NULL) {
        printf("No Memory\n");
        exit(1);
    }
    for (int i=0; i<row; i++) {
        (*matrix)[i]=(int*)malloc(column*sizeof(int));
        if ((*matrix)[i]==NULL) {
            printf("No Memory\n");
            exit(1);
        }
    }
    printf("Enter Matrix in size: %d*%d\n",row,column);
    for (int i=0; i<row; i++) {
        for (int j=0; j<column; j++) {
            scanf("%d",&(*matrix)[i][j]);
        }
    }
    if (row==column) {
        sizeMatrix=row;
        subMat=SubMatrix(*matrix, sizeMatrix, pSizeMatrix);
        printf("----The Matrix is---- SIZE ->[%d*%d]\n",row,row);
        PrintMatrix(*matrix, row, column);
        row=*pSizeMatrix;
        column=*pSizeMatrix;
        printf("----The SubMatrix is---- SIZE ->[%d*%d]\n",row,row);
        PrintMatrix(subMat, row, column);
        FreeMatrix(&subMat, row);
    }else{
        printf("----The Matrix is----\n");
        PrintMatrix(*matrix, row, column);
    }

}//The function gets a pointer to a dynamic 2D array and the amount of rows, freeing up all the memory the matrix has captured.
void FreeMatrix(int*** matrix,int row){
    for(int i=0;i<row;i++)
        free((*matrix)[i]);
    free(*matrix);
}
//The function will get a dynamic 2D array, the number of rows, and the number of columns. The function prints the matrix organs in a 2D table view.
void PrintMatrix(int** matrix ,int row,int colum){
    for (int i=0; i<row; i++) {
        for (int j=0; j<colum; j++) {
            printf("%d    ",matrix[i][j]);
        }
        printf("\n");
    }
}
//The function receives a 2D array - a square matrix of integer values. The function returns the quadratic sub-matrix whose limb sum is the maximum.
int** SubMatrix(int** matrix ,int sizeMatrix, int*pSizeMatrix){
    int indexRow=0,indexCol=0;
    int temp_sum=0,sum=0,temp_size=0;
    int flag=0,counter=0;
    int** subMat=NULL;
    while (*pSizeMatrix!=0) {
        flag=0;
        counter=0;
        for (int i=0; i<sizeMatrix && flag == 0; i++) {
            for (int j=0; j<sizeMatrix && flag == 0; j++) {
                sum=SumSubMatrix(matrix, i, j, pSizeMatrix,&counter,sizeMatrix);
                if (sum>temp_sum) {
                    temp_sum=sum;
                    indexRow=i;
                    indexCol=j;
                    temp_size=*pSizeMatrix;
                    if (counter == (*pSizeMatrix)*(*pSizeMatrix)) {
                        flag=1;
                    }
                }
            }
        }
        *pSizeMatrix=*pSizeMatrix-1;
    }
    subMat=(int**)malloc(temp_size*sizeof(int*));
    if (subMat==NULL) {
        printf("NO MEMORY\n");
        FreeMatrix(&matrix, sizeMatrix);
        exit(1);
    }
    for (int i=0; i<temp_size; i++){
        subMat[i]=(int*)malloc(temp_size*sizeof(int));
        if (matrix[i]==NULL) {
            printf("No Memory\n");
            free(subMat);
            FreeMatrix(&matrix, sizeMatrix);
            exit(1);
        }
    }
    if (temp_sum!=0){
           for (int t=0 ,i=indexRow; t<temp_size && i<temp_size+indexRow; t++ , i++) {
               for (int l=0 ,j=indexCol; l<temp_size && j<indexCol+temp_size; l++ , j++) {
                   if (i<sizeMatrix && j<sizeMatrix)
                       subMat[t][l]=matrix[i][j];
                }
           }
    }
    *pSizeMatrix=temp_size;
    return subMat;
}
//The function receive a matrix and its size and it receives the index from which it will begin to calculate the sum of the sub-matrix and return the amount it exits.
int SumSubMatrix(int** matrix,int indexRow,int indexCol, int* sizeMatrix,int* counter,int size){
    int sum=0;
    *counter=0;
    for (int i=indexRow; i<indexRow+*sizeMatrix; i++) {
        for (int j=indexCol; j<indexCol+*sizeMatrix; j++) {
            if (i<size && j<size){
                *counter=*counter+1;
                sum+=matrix[i][j];
            }
        }
    }
    return sum;
}
