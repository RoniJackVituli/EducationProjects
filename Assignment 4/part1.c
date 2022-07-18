 
//
//  Part1.c
//  Created by Roni Jack Vituli. ID 315369967.
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 80
#define NO_ERROR 0
//Declaration of functions
char* CreateNewString(char *str);
void RemoveEnter(char str[]);
int* BuildArray(int* size);
void PrinyArray(int* arr,int size);
int* MerageTwoArrays(int* arr1, int size1,int* arr2,int size2,int *newSize);
void copyArrays(int* arr1,int* arr2);
//The main program receives a string and passes it to the first function and prints the new string that the function returns. Then, using the functions of the second task, the main program creates 2 arrays, merges them into one array, prints the merged array and finally releases all memory.
int main(){
    char str[SIZE];
    char *newArry;
    int size1,size2,newSize;
    int* arr1,*arr2,*MerageArry;
    printf("Enter a sequence of characters\nexample: 'aaaabbbbcccc'\n");
    fgets(str, SIZE, stdin);
    RemoveEnter(str);
    newArry=CreateNewString(str);
    arr1=BuildArray(&size1);
    arr2=BuildArray(&size2);
    MerageArry=MerageTwoArrays(arr1, size1, arr2, size2, &newSize);
    printf("----The new string---\n");
    printf("%s\n",newArry);
    free(newArry);
    printf("-----The Merage between arr1 and arr2-----\n");
    printf("The first Array is --> ");
    PrinyArray(arr1, size1);
    printf("\nThe sec Array is --> ");
    free(arr1);
    PrinyArray(arr2, size2);
    printf("\nThe Merage is --> ");
    free(arr2);
    PrinyArray(MerageArry, newSize);
    free(MerageArry);
    return NO_ERROR;
}


//The function creates and returns a new string so that each sequence of characters from the previous string is replaced by two characters: the character that is repeated in sequence, and a digit representing the sequence length.
//For example:
//String Received: aaabbbbccdddddd Returned String: a3b4c2d6
char* CreateNewString(char *str){
    int i=0,counter,k=0,size=0;
    char ch,buffer[SIZE],*newArr;
    while(str[i]!='\0'){
        counter=1;
        for (int j=i; str[j]==str[j+1]; j++) {
            ch=str[j];
            counter++;
            i=j+1;
        }
        buffer[k] = str[i];
        k++;
        buffer[k] = counter + '0';
        k++;
        i++;
        if (str[i]=='\0')
            buffer[k]='\0';
    }
    size=(int)strlen(buffer);
    newArr=(char*)malloc(size*sizeof(char));
    if (newArr==NULL) {
           printf("no memory\n");
           exit(1);
       }
    for (int i=0; i<size; i++) {
        newArr[i]=buffer[i];
    }
    return newArr;
}
//The function receive an array and removes the Enter character.
void RemoveEnter(char str[]){
    int i=0;
    char ch;
    while (str[i]!='\0') {
        ch=str[i];
        if (ch=='\n') {
            str[i]='\0';
        }
        i++;
    }
}


//The function input the size of the array from the end user Accordingly, it fills it with values as input from the user and returns the new array.
int* BuildArray(int* size){
    printf("Enter size of array you want\n");
    scanf("%d",size);
    int* arr = (int*)malloc((*size)*sizeof(int));
    if (arr==NULL) {
        printf("no memory\n");
        exit(1);
    }
    if(*size!=0){
        printf("Enter %d numbers\n",*size);
        for (int i=0; i<*size; i++)
            scanf("%d",&arr[i]); 
    }
    return arr;
}
//The function receive an array parameter, including its size, and prints the array organs in the following format.
void PrinyArray(int* arr,int size){
    printf("(");
    for(int i=0; i<size;i++){
        printf("%d" ,arr[i]);
        if(i+1 < size){
            printf(", ");
        }
    }
    printf(")\n");
}

//The function takes two arrays and copies the array to another array.
void copyArrays(int* arr1,int* arr2){
    for (int i=0; arr1[i]!='\0'; i++) {
        arr2[i]=arr1[i];
        if (arr1[i+1]=='\0')
            arr2[i+1]='\0';
    }
}

//The function receives two arrays of arr1 and arr2 integers of sizes1 and size2 sorted in ascending order, creates and returns the new sorted array containing arrays and arr2 arrays without repeating organs.
int* MerageTwoArrays(int* arr1, int size1,int* arr2,int size2,int *newSize){
    int sameNum=0,t=0,j=0,i=0;
    int *pArr;
    for (int i=0; i<size1; i++) {
        for (int j=0; j<size2; j++) {
            if (arr1[i]==arr2[j]) {
                sameNum++;
            }
        }
    }
    *newSize=size1+size2-sameNum;
    int* newArr=(int*)malloc((*newSize)*sizeof(int));
    if (newArr==NULL) {
        printf("no memory\n");
        exit(1);
    }
    if(size1!=0 && size2!=0){
        while (j < size1 && t < size2 ) {
            if (arr1[j] < arr2[t]) {
                newArr[i] = arr1[j];
                j++;
            }else if(arr1[j] > arr2[t]){
                newArr[i] = arr2[t];
                t++;
            }else if(arr1[j] == arr2[t]){
                newArr[i] = arr1[j];
                j++;
                t++;
            }
            i++;
            if (t==size2) {
                for (; i < *newSize ; i++){
                    newArr[i]=arr1[j];
                    j++;
                }
            }else if(j==size1){
                for (; i < *newSize ; i++){
                    newArr[i]=arr2[t];
                    t++;
                }
            }
        }
        return newArr;
    }else if(size1==0){
        pArr=(int*)malloc(size2*sizeof(int));
        if (pArr==NULL) {
            printf("no memory\n");
            exit(1);
        }
        copyArrays(arr2, pArr);
        return pArr;
    }else
        pArr=(int*)malloc(size1*sizeof(int));
        if (pArr==NULL) {
            printf("no memory\n");
            exit(1);
        }
        copyArrays(arr1, pArr);
        return pArr;
}
