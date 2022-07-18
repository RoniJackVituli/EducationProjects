//
//  Part2.c
//  assignment3
//  Author: Roni Jack Vituli
//  ID: 315369967

#include <stdio.h>
#define NO_ERROR
#define ROW 4
#define COLUMN 4
#define M 8 //ROWS
#define N 10//COLUMN
typedef enum {FALSE,TRUE} BOOL;
//Declaration of functions
void MultipliersDividers(int arr[][COLUMN],int indexRow ,int indexColumn);
void MaxZeroArea(int arr[][N],int length);
int counterZero(int arr[][N],int indexRow,int indexCol,int length);
void printArray(int arr[][N]);
int checkLength(int length);
int checkRow(int Row);
int checkColumn(int column);

//Main function that make two 2D arrays, initializes the arrays with user input and also input another value called as length. The program will then run the MultipliersDividers and MaxZeroArea functions.
int main(){
    int firstArr[ROW][COLUMN],secArr[M][N];
    int length, indexRow,indexColumn;
    printf("Please enter %d*%d numbers\n",ROW,COLUMN);
    for (int i=0; i<ROW; i++) {
        for (int j=0; j<COLUMN; j++)
            scanf("%d",&firstArr[i][j]);
    }
    printf("Enter Row\n");
    scanf("%d",&indexRow);
    indexRow=checkRow(indexRow);
    printf("Enter Column\n");
    scanf("%d",&indexColumn);
    indexColumn=checkColumn(indexColumn);
    printf("Please Enter %d*%d only 0 or 1 \n",M,N);
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            scanf("%d",&secArr[i][j]);
            while (secArr[i][j]!=0 && secArr[i][j]!=1) {
                printf("Please Enter ONLY 1 or 0\n");
                scanf("%d",&secArr[i][j]);
            }
        }
    }
    printf("Enter length you want\n");
    scanf("%d",&length);
    length=checkLength(length);
    MultipliersDividers(firstArr, indexRow, indexColumn);
    MaxZeroArea(secArr, length);
}//end function main

//A MultipliersDividers function that receives a square matrix and two additional numbers that are the position of an organ in an array and prints the number of numbers in an array that are duplicates of that organ and also the number of its multiples.
void MultipliersDividers(int arr[][COLUMN],int indexRow ,int indexColumn){
    printf("---------Function Multipliers Dividers---------\n");
    int countMulti=0;
    int countDivision=0;
    printf("\nThe value is: %d\n",arr[indexRow][indexColumn]);
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COLUMN; j++){
            if (arr[i][j] > arr[indexRow][indexColumn] && arr[i][j]!=0) {
                if (arr[i][j] % arr[indexRow][indexColumn]==0)
                    countMulti++;
            }else if(arr[i][j] < arr[indexRow][indexColumn] && arr[i][j]!=0){
                if (arr[indexRow][indexColumn] % arr[i][j]==0)
                    countDivision++;
            }
        }
    }
    printf("countMulit == %d\ncountDivision == %d\n",countMulti,countDivision);
}

//A function MaxZeroArea that receives a matrix of size M rows and N columns containing only 0 or 1 and an additional length. The function will find the square sub matrix of length * length that contains the most zeros.
void MaxZeroArea(int arr[][N],int length){
    printf("\n---------Function MaxZeroAerea---------\n\n");
    printf("\n--Original Matrix %d*%d--\n",M,N);
    printArray(arr);
    printf("\n");
    int counter=0,temp=0;
    int startIndexRow=0,startIndexColum=0;
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            counter=counterZero(arr,i,j,length);
            if (counter>temp) {
                temp=counter;
                startIndexRow=i;
                startIndexColum=j;
            }
        }
    }
    if (temp!=0){
        printf("\n--Sub Matrix--\n");
        for (int i=startIndexRow; i<length+startIndexRow; i++) {
            for (int j=startIndexColum; j<startIndexColum+length; j++) {
                printf("%d  ",arr[i][j]);
            }
            printf("\n");
        }
        printf("Sub Matrix starts at indexes [%d][%d], length = %d : %d Zeros\n",startIndexRow,startIndexColum,length,temp);
    }else{
        printf("THERE ARE NOT ZERO IN THIS MATRIX\n");
    }
    
}
//This function that counts the number of zeros by the sub-matrix and returns exactly how many zeros there is where a sub-matrix checks!
int counterZero(int arr[][N],int indexRow,int indexCol,int length){
    int counter=0;
    for ( int i=indexRow; i<length+indexRow; i++) {
        for (int j=indexCol; j<indexCol+length; j++){
            if (i<M && j<N) {
                if (arr[i][j]==0)
                    counter++;
            }
        }
    }
    return counter;
}
//This function prints the matrix!
void printArray(int arr[][N]){
    for (int i=0; i<M; i++) {
        for (int j=0; j<N; j++) {
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}//end function prinArray;

int checkLength(int length){
    while (length>M || length>N){
        printf("Enter New length\n");
        scanf("%d",&length);
    }
    return length;
}
//Checks if the rows the user has inserted correctly
int checkRow(int Row){
    while (Row>=ROW || Row<0) {
        printf("Enter correct Row between 0-%d\n",ROW-1);
        scanf("%d",&Row);
    }
    return Row;
}//end checkRow.

//Checks if the colum the user has inserted correctly
int checkColumn(int Col){
    while (Col>=COLUMN || Col<0) {
        printf("Enter correct column between 0-%d\n",COLUMN-1);
        scanf("%d",&Col);
    }
    return Col;
}//end checkColumn
