//  Part3
//  Created by Roni Jack Vituli, ID:315369967
//  Copyright © 2020 Roni Jack Vituli. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
#define NO_ERROR 0
enum {FALSE,TRUE};
char** GetAllNames(int* countNames);
//Declaration of variables
void FreeAllNames(char*** names,int countNames);
void PrintAllNames(char** names,int countNames);
void UpdateAllNames(char** names, int countNames);
void SortAllNames (char*** names, int countNames);
void ChangeString(char** names,char** buffer,int countNames);
void RestString(char** str,int size);
//The main program, which builds a set of names, corrects it, sorts, prints and eventually releases all memory.
int main() {
    int countNames=0;
    char** Names=NULL;
    Names=GetAllNames(&countNames);
    UpdateAllNames(Names,countNames);
    printf("\n-----The names sorted by alphabet-----\n");
    SortAllNames(&Names, countNames);
    PrintAllNames(Names, countNames);
    FreeAllNames(&Names, countNames);
    return NO_ERROR;
}
//The function inputs the number of names requested, and creates an array accordingly and fills it with the user input data.
char** GetAllNames(int* countNames){
    char** names=NULL;
    printf("How many names do you want?\n");
    scanf("%d",countNames);
    getchar();
    names=(char**)malloc((*countNames)*sizeof(char*));
    if (names==NULL) {
        printf("No memory\n");
        exit(1);
    }
    for (int i=0; i<*countNames ; i++) {
        names[i]=(char*)malloc(MAX*sizeof(char));
        if (names[i]==NULL) {
            printf("no memory in index %d\n",i);
            exit(1);
        }
    }
    printf("Enter %d names\n",*countNames);
    for (int i=0; i<*countNames; i++) {
        fgets(names[i], MAX, stdin);
    }
    return names;
}
//The function receive array names and also the size of array and frees all memory that the array takes.
void FreeAllNames (char*** names,int countNames){
    for (int i=0; i<countNames; i++) {
        free((*names)[i]);
    }
    free(*names);
}
//The function receives array names and its size and prints the names there are in the array
void PrintAllNames (char** names,int countNames){
    for (int i=0; i<countNames; i++) {
           printf("%s",names[i]);
       }
}
//The function gets an array of names and their size and deletes all unnecessary spaces. leaving one space between the last name and the first name.
void UpdateAllNames(char** names, int countNames){
    int flag = FALSE;
    int indexCol=0;
    char** buffer=NULL;
    buffer=(char**)malloc(countNames*sizeof(char*));
    if (buffer==NULL) {
        printf("No memory in buffer\n");
        exit(1);
    }
    for (int i=0; i<countNames; i++) {
        buffer[i]=(char*)malloc(MAX*sizeof(char));
        if (buffer[i]==NULL) {
            printf("no memory in buffer on index %d ",i);
            exit(1);
        }
    }
    for (int i=0; i<countNames; i++) {
        for (int j=0; names[i][j]!='\0'; j++){
            flag=FALSE;
            if (names[i][j]==' ')
                flag=TRUE;
            if(flag==FALSE){
                buffer[i][indexCol]=names[i][j];
                indexCol++;
                if (names[i][j+1]==' ') {
                    buffer[i][indexCol]=names[i][j+1];
                    indexCol++;
                }
            }
        }
        indexCol=0;
    }
    RestString(names,countNames);
    ChangeString(names, buffer, countNames);
    FreeAllNames(&buffer, countNames);
}
//The function makes a placement from one array to another.
void ChangeString(char** names,char** buffer,int countNames){
    for (int i=0; i<countNames; i++) {
        for (int j=0; buffer[i][j]!='\0'; j++) {
            names[i][j]=buffer[i][j];
        }
    }
}
//The function fills the array with the character of '\ 0'
void RestString(char** str,int size){
    for (int i=0; i<size; i++) {
        for (int j=0; str[i][j]!='\0'; j++) {
            str[i][j]='\0';
        }
    }
}
//The function receives an array of names and their size and sorts it in ascending lexicographic order by surname and first names.
void SortAllNames (char*** names, int countNames){
    char* temp=NULL;
    temp=(char*)malloc(MAX*sizeof(char));
    if (temp==NULL) {
        printf("no memory for temp\n");
        exit(1);
    }
    for (int i=0; i<countNames; i++) {
        for (int j=i+1; j<countNames; j++){
            if (strcmp((*names)[i], (*names)[j]) > 0){
                strcpy(temp, (*names)[i]);
                strcpy((*names)[i], (*names)[j]);
                strcpy((*names)[j], temp);
            }
        }
    }
    free(temp);
}
