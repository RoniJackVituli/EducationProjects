//Assignment 3 Part3
//Author: Roni Jack Vituli
//ID: 315369967
#include <stdio.h>
#define ROW 4
#define length 50
#define NO_ERROR 0
#define alphabet 26
typedef enum {FALSE,TRUE} BOOL;
//Declaration of functions
void reverseLetters(char str[],int size);
void reverseWords(char str[],int size);
void upperLower(char str[]);
void findAnagrams(char str[][length]);
int counterLetters(char str[][length], int row);
void changeCharToLow(char str[]);
int StrlenArr(char str[][length],int row);
int Strlen(char str[]);
void RemoveEnter(char str[]);
void RemoveEnterArr(char str[][length],int row);
void SendToFunc(char str[]);
BOOL sameString(char str1[], int row1, char str2[],int row2);
BOOL NewStrings(char str1[][length],int row1, char str2[][length],int row2);

//function main.
//The function creates a string and an array of strings, filling them in the data as input from the user,then it calls each of the first 3 functions with the SendTofunc function, and prints the string after the change.
int main() {
    char str1[length];
    char arrStr[ROW][length]; // arrays of strings
    printf("Input the first String\n");
    fgets(str1,length,stdin);
    printf("Now you need to fill array of strings\n");
    for (int num=1,i=0; i<ROW; num++, i++) {
        printf("Input to line %d\n",num);
        fgets(arrStr[i], length, stdin);
    }
    printf("-------Anagrams---------\n");
    findAnagrams(arrStr);
    printf("\n---------All the three functions----------\n");
    SendToFunc(str1);
    return NO_ERROR;
}//end function main

//This function receive a the frist string from the main and send the string to three function!
void SendToFunc(char str[]){
    int size;
    RemoveEnter(str);
    size=Strlen(str);
    char buffer[size];
    for (int i=0; str[i]!='\0'; i++){
        buffer[i]=str[i];
        if (str[i+1]=='\0')
            buffer[i+1]='\0';
    }
    reverseLetters(buffer,size);
    printf("Function ReverseLetters -----> %s\n",buffer);
    for (int i=0; str[i]!='\0'; i++) {
           buffer[i]=str[i];
       }
    reverseWords(buffer, size);
    printf("Function ReverseWords -----> %s\n",buffer);
    for (int i=0; str[i]!='\0'; i++) {
           buffer[i]=str[i];
       }
    upperLower(buffer);
    printf("Function UpperLower -----> %s\n",buffer);
}//end Function SendToFunc

//This Function receive string and size of string and reverse the letter.
//exmaple Roni to inoR
void reverseLetters(char str[],int size){
    char buffer[size];
    int temp_i,j=0;
    for (int i=0; i<size; i++) {
        if(str[i] == ' ' || str[i] == '\0') {
            temp_i = i-1;
            while(j<i) {
                buffer[j] = str[temp_i];
                j++;
                temp_i--;
            }
            if(str[i] == '\0'){
                buffer[j]='\0';
            }else {
                buffer[j]=' ';
            }
            j++;
        }
    }
    for (int i=0; i<size; i++) {
       str[i] = buffer[i];
    }
}//end function reverseLetters

//This function receive a string and the size of the string and Changes the compositor from end to start
//example "Roni Jack Vituli" to "Vituli Jack Roni"
void reverseWords(char str[],int size){
    char buffer[size];
    int temp_i=0,indexCoun=0,j=0;
    int temp_j=0;
    for (int i=size-1; i>0; i--) {
        if (str[i] == ' ' || str[i] == '\0'){
            temp_i=i-1;
            indexCoun=0;
            while (str[temp_i] != ' ' && str[temp_i] != '\0') {
                indexCoun++;
                temp_i--;
            }
            temp_i++;
            j=0;
            while (j<indexCoun) {
                buffer[temp_j]=str[temp_i];
                temp_j++;
                j++;
                temp_i++;
            }
            if (str[temp_i] == '\0' || str[temp_i] == ' ') {
                buffer[temp_j]=' ';
                if (temp_j==size-1) {
                    buffer[temp_j]='\0';
                }
            }
            temp_j++;
            temp_i-=indexCoun;
        }
    }
    for (int i=0; i<size; i++) {
        str[i] = buffer[i];
    }
}//end funtion reverseWord.

//This function receive a string and change the small letter to big and turned
//example "RoNi" to "rOnI"
void upperLower(char arr[]){
    char ch;
    int i=0;
        while (arr[i]!='\0') {
            ch=arr[i];
            if (ch>='A' && ch<='Z')
                arr[i]=arr[i]+32;
            else if(ch>='a' && ch<='z')
                arr[i]=arr[i]-32;
            i++;
        }
}//end funtion upperLower.

//This function receive an array of strings and checks for anagrams between them.
void findAnagrams(char str[][length]){
    int i=0;
    int j, flag=0;
    while(i<ROW){
        j=i+1;
        RemoveEnterArr(str, i);
        while (j<ROW) {
            RemoveEnterArr(str, j);
            if (counterLetters(str,i) == counterLetters(str,j)) {
                if (NewStrings(str, i, str, j)){
                    printf("%s == %s\n",str[i],str[j]);
                    flag=1;
                }
            }
            j++;
        }
        i++;
    }
    if(flag==0){
        printf("\nThere are not Anagrams in this array of Strings\n");
    }
}
//This Function receive a string and bring back how many letters they have.
//exaple "roni" ----> counter will return 4;
int counterLetters(char str[][length],int row){
    int counter=0;
    int col=0;
    while(str[row][col]!='\0'){
        counter++;
        col++;
    }
    return counter;
}
//The function receives two strings and copies them to two new strings and sends them to see if they are equal by sameString function.
BOOL NewStrings(char str1[][length],int row1, char str2[][length],int row2){
    int size1,size2;
    int col1=0,col2=0,i=0,j=0;
    size1=StrlenArr(str1, row1);
    size2=StrlenArr(str2, row2);
    char newStr1[6];
    char newStr2[size2];
    while (str1[row1][col1]!='\0') {
           newStr1[i]=str1[row1][col1];
           i++;
           col1++;
       }
    while (str2[row2][col2]!='\0') {
        newStr2[j]=str2[row2][col2];
        j++;
        col2++;
    }
    RemoveEnter(newStr1);
    RemoveEnter(newStr2);
    changeCharToLow(newStr1);
    changeCharToLow(newStr2);
   return sameString(newStr1, row1, newStr2, row2);
}//end funtion NewStrings

//This function makes the characters lowercase.
void changeCharToLow(char str[]){
    char ch;
    int i=0;
    while (str[i]!='\0') {
        ch=str[i];
        if (ch>='A' && ch<='Z')
            str[i]=str[i]+32;
        i++;
    }
}//end changeCharToLow

//This function checks the length of the array
int StrlenArr(char str[][length],int row){
    int size=0;
    int col=0;
    while (str[row][col]!='\0') {
        size++;
        col++;
    }
    return size;
}

int Strlen(char str[]){
    int count=0,i=0;
    while (str[i]!='\0') {
        count++;
        i++;
    }
    count++;
    return count;
}//end Strlen

//The function alternates between the character '\n' to '\0'
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
void RemoveEnterArr(char str[][length],int row){
    int col=0;
    char ch;
    while (str[row][col]!='\0') {
        ch=str[row][col];
        if (ch=='\n') {
            str[row][col]='\0';
        }
        col++;
    }
}
//This Function receive two string and check if they equal function retun true else fulse.
BOOL sameString(char str1[], int row1, char str2[],int row2){
    char alp[alphabet]="abcdefghijklmnopqrsyuvwxyz";
    int counter=0;
    int bufferOne[alphabet]={0};
    int bufferTwo[alphabet]={0};
    int j=0,t=0;
    for (int i=0; alp[i]!='\0'; i++) {
        j=0;
        while (str1[j]!='\0'){
            if (alp[i]==str1[j])
                bufferOne[i]=bufferOne[i]+1;
           j++;
        }
    }
    for (int i=0; alp[i]!='\0'; i++) {
        t=0;
        while (str2[t]!='\0'){
            if (alp[i]==str2[t])
                bufferTwo[i]=bufferTwo[i]+1;
            t++;
        }
    }
    for (int i=0; i<alphabet; i++) {
        if(bufferOne[i]==bufferTwo[i]){
            counter++;
        }
    }
    if (counter==alphabet)
        return TRUE;
    else
        return FALSE;
}
