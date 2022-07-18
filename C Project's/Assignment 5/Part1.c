//Part1
//Campus:Beer Sheva
//Author: Roni Jack Vituli ID:315369967.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NO_ERROR 0
#define sizeOne 7
#define sizeTwo 4
#define MAX 80
typedef enum {FALSE,TRUE} BOOL;
BOOL onlyEven(int number);
int SumRang(int high, int low);
long RemoveDigit(long number,int num);
BOOL CheckArrays(int arr1[],int arr2[],int size2);
BOOL IsInArray(int arr[],int size,int num);
void UpdateArray(int arr[],int size,int num);
char* FristOccurenceUpper(char* str);
BOOL CheckString(char* str1,char* str2);


int main(){
//-------------------------------------Question Number 1------------------------------------------
    printf("\n-------------------------------------Question Number 1------------------------------------------\n");
    int high=15,low=10;
    printf("The Results is: %d\n",SumRang(high, low));
//-------------------------------------Question Number 2------------------------------------------
    printf("\n-------------------------------------Question Number 2------------------------------------------\n");
    int number=26842;
    if(onlyEven(number))
        printf("All digits are even\n");
    else
        printf("NOT all digits are even\n");
//-------------------------------------Question Number 3------------------------------------------
    printf("\n-------------------------------------Question Number 3------------------------------------------\n");
    long number1=35725;
    int num=5;
    printf("The new Number after remove the num you choice: %ld\n",RemoveDigit(number1, num));
//-------------------------------------Question Number 4------------------------------------------
    printf("\n-------------------------------------Question Number 4------------------------------------------\n");
    int arr1[sizeOne]={7,36,125,321,245,20,1};
    int arr2[sizeOne]={1,20,245,321,125,36,7};
    if(CheckArrays(arr1, arr2,sizeOne))
        printf("An array is equal to the second array in reverse order\n");
    else
        printf("An array is NOT equal to the second array in reverse order\n");
//-------------------------------------Question Number 5+6------------------------------------------
    printf("\n-------------------------------------Question Number 5+6------------------------------------------\n");
    int num1=10;
    int arr[]={4,5,7,2};
    if(IsInArray(arr, sizeTwo, num1))
        printf("The value appears in the given array\n");
    else
        printf("The value does not appear in the given array\n");
    UpdateArray(arr, sizeTwo, num1);
    printf("The New array multi with num you choice: ");
    for (int i=0; i<sizeTwo; i++)
        printf("%d ",arr[i]);
//-------------------------------------Question Number 7------------------------------------------
    printf("\n-------------------------------------Question Number 7------------------------------------------\n");
    char str[MAX]="testThisString";
    char *Pstr=NULL;
    Pstr=FristOccurenceUpper(str);
    if (Pstr==NULL)
        printf("\nNULL\n");
    else
        printf("\nThe char is '%c'\n",*Pstr);
//-------------------------------------Question Number 8------------------------------------------
    printf("\n-------------------------------------Question Number 8------------------------------------------\n");
    char Str[MAX]="PeacEpeace";
    char *Pstr1=NULL, *Pstr2=NULL;
    int size = 0;
    for (int i=0; Str[i]!='\0'; i++)
        size++;
    Pstr1=Str;
    Pstr2=&Str[size/2];
    if(CheckString(Pstr1,Pstr2))
        printf("The first half and the second half of the string are equal\n");
    else
        printf("The first half and the second half of the string are NOT equal\n");
    
    return NO_ERROR;
}

//------------------------------------------The recursive functions------------------------------------

//Sum Range function that receives as a parameter two integers low and high and returns the sum of all integers in the [high, .., low] section.
int SumRang(int high,int low){
    if (high==low)
        return low;
    else
        return low+SumRang(high, low+1);
}
//A boolean function called OnlyEven that receives an integer and returns true if all digits of the number are parity, otherwise returns false
BOOL onlyEven(int number){
    if(number==0)
        return TRUE;
    else if(number%2)
        return FALSE;
    else
        return onlyEven(number/10);
}
//A function called RemoveDigit that receives a long integer and a number, returns the number that is obtained after downloading all instances of the digit by a number. If the number does not appear at all, the function returns the original number.
long RemoveDigit(long number,int num){
    if (number==0) {
        return 0;
    }else if(number%10==num){
        return RemoveDigit(number/10, num);
    }
    else
        return number%10+RemoveDigit(number/10, num)*10;
}
//Boolean function CheckArrays which receives as two parameters and their size. Arrays of the same size - The function returns true if each array is equal to the other array in reverse order. Otherwise, it returns a lie.
BOOL CheckArrays(int arr1[],int arr2[],int size2){
    if (size2==0)
        return TRUE;
    else if (arr2[size2-1]==*arr1)
        return CheckArrays(arr1+1,arr2,size2-1);
    else
        return FALSE;
}
//The IsInArray boolean function receives an array of integers including its size and additional value. The function checks whether the value appears in the array, if the function returns true, otherwise returns false.
BOOL IsInArray(int arr[],int size,int num){
    if (size<0)
        return FALSE;
    if (arr[size-1]==num)
        return TRUE;
    else
        return IsInArray(arr, size-1, num);
}
//The UpdateArray function receives an array of integers including its size and additional value. The function multiplies each organ in the array by this number.
void UpdateArray(int arr[],int size,int num){
    if (size>0){
        arr[size-1]*=num;
        UpdateArray(arr, size-1, num);
    }
}
//The FirstOccurenceUpper function accepts a string and returns the pointer to the first occurrence of a character which is a large Latin letter. If no large signal appears, the function returns NULL
char* FristOccurenceUpper(char* str){
    if (*str == '\0') {
        return str=NULL;
    }
    if (*str >= 'A' && *str <= 'Z') {
        return str;
    }
    return str=FristOccurenceUpper(str+1);
}
//A CheckString boolean function that receives as a parameter points to the beginning of the string and points to the middle of the string and checks whether its first half is identical to the second without reference to a small and large letter That is, the letters 'A' and 'a' are considered the same. The function returns true if there is another difference it returns false.
BOOL CheckString(char* str1,char* str2){
    if (*str2=='\0')
        return TRUE;
    if (*str1 >= 'A' && *str1 <= 'Z')
        *str1+=32;
    if (*str2 >= 'A' && *str2 <= 'Z')
        *str2+=32;
    if (*str1!=*str2)
        return FALSE;
    return CheckString(str1+1, str2+1);
}
