//  Part1.c
//  assignment3
//  Author: Roni Jack Vituli
//  ID: 315369967

#include <stdio.h>
#define NO_ERRORS 0
#define sizeOne 6
#define sizeTwo 14
#define sizeThree 12
typedef enum {FALSE,TRUE} BOOL;
int isBalanced(int arr[] , int size);
void CommonPart(int arr1[],int size1,int arr2[],int size2);

//The function main fills all arrays with user input and sends the first array to the isBalanced function and prints the "middle index" if it exists, or a suitable message if it is notExisting, then the program will send the 2 additional arrays to the CommonPart function.
int main(){
    int arr1[sizeOne],arr2[sizeTwo],arr3[sizeThree];
    printf("Enter %d numbers\n",sizeOne);
    for (int i=0; i<sizeOne; i++)
        scanf("%d",&arr1[i]);
    printf("Enter %d numbers\n",sizeTwo);
    for (int i=0; i<sizeTwo; i++)
        scanf("%d",&arr2[i]);
    printf("Enter %d numbers\n",sizeThree);
    for (int i=0; i<sizeThree; i++)
        scanf("%d",&arr3[i]);
    if (isBalanced(arr1,sizeOne)==-1)
        printf("There is no middle index\n");
    else
        printf("The middle index on array 1 is %d\n\n",isBalanced(arr1, sizeOne));

    printf("The COMMON PART BETWEEN ARRAY 2 AND ARRAY 3\n");
    CommonPart(arr2, sizeTwo,arr3,sizeThree);

    return NO_ERRORS;
}

//This The function receives an array of integers, including its size, and checks whether an array index exists and returns it, otherwise the function returns a value of 1-.
int isBalanced(int arr[], int size){
    int sum1,sum2;
    int midIndex = 0,flag=0;
    for(int i=0 ; i<size && flag==FALSE; i++){
        sum1=0;
        sum2=0;
        for (int j=0; j<=i; j++) // this lop run until index i and calculate the sum!
            sum1+=arr[j];
        for(int j=i+1; j<size; j++)// this lop run from i+1 until size of array and calculate the sec sum.
            sum2+=arr[j];
        if (sum1==sum2){
            midIndex=i;
            flag=TRUE;
        }
    }
    if(flag==TRUE)
        return midIndex;
    else
        return -1;
}//end function isBalaced.


//The function receives two arrays of numbers integers, including their size and prints the overlapping portion (shared between the end of the first array and the beginning of the second array) at its maximum length and length
void CommonPart(int first[],int size1,int sec[],int size2){
    int counter=0,temp=0;
    int indexOne,indexTwo;
    for (int i=size1-1,j=0 ;j<size2;j++){
        if(size1>size2){
            if (counter>temp) {
                temp=counter;
            }
            indexTwo=j;
            indexOne=i;
            counter=0;
            while (indexTwo>=0){
                if(first[indexOne]==sec[indexTwo]){
                    indexOne--;
                    indexTwo--;
                    counter++;
                }else{
                    indexOne--;
                    indexTwo--;
                    counter--;
                }
            }
        }else{
            
        }
    }
    if (temp>0) {
        printf("Max Common part: {");
        for (int FinalIndex=0; FinalIndex<temp; FinalIndex++) {
            printf("%d",sec[FinalIndex]);
            if (FinalIndex<temp-1) {
                printf(",");
            }
        }
         printf("},Length = %d\n",temp);
    }else{
        printf("They have nothing in common\n");
    }
    
}//end function CommonPart!
