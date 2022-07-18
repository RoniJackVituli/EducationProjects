//Part2
//Campus:Beer Sheva
//Author: Roni Jack Vituli ID:315369967.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 80
#define Grade 4
#define NO_ERROR 0
#define LONGPASS 4
void read_from_txt(void);
char* newBuffer(char* buffer , int size);
int main(){
    read_from_txt();
    return NO_ERROR;
}//The read_from_txt function that reads data from a text file called txt.passwords containing passwords, where all A password in a file appears in a separate line and writes to an output file called txt.weakpass the passwords weakening". The "weak" password has a score less than 4. The password contains (lower or upper case) letters, digits and the following special characters: @ and% only. The score calculation rules are:
//1) If the password contains both uppercase and lowercase letters - extra 2 points for marking.
//2) If there is at least one digit - an extra 2 points to be added to section 1.
//3) If there is at least one special mark (@ or %) - an additional 3 points to mark item 1 and 2.
//4) If the password length is longer than 6 characters - an extra 3 points for all section Previous.

void read_from_txt(){
    FILE* inputFileP=NULL,*outputFileP=NULL;
    char *temp;
    char password[80];
    int count1=0,count2=0,count3=0,i=0;
    int lenCount=0 ,sum=0;
    inputFileP=fopen("passwords.txt","r");
    if(inputFileP==NULL){
        printf("no memory scr\n");
        exit(0);
    }
    outputFileP=fopen("weakpass.txt", "w");
    if (outputFileP==NULL) {
        printf("no memory\n");
        fclose(inputFileP);
        exit(1);
    }
    while (fscanf(inputFileP,"%s",password) != EOF) {
        temp=newBuffer(password, (int)strlen(password));
        while(temp[i]!='\0'){
            if((temp[i] >= 'a' && temp[i] <= 'z' && count1 == 0) || (temp[i] >= 'A' && temp[i] <= 'Z' && count1 == 0))
                count1=+2;
            else if(temp[i] >= '0' && temp[i] <= '9' && count2 == 0)
                count2=+2;
            else if((temp[i] == '@' || temp[i] == '%') && count3 == 0)
                count3=+2;
            lenCount++;
            i++;
        }
        sum=count1+count2+count3;
        if (lenCount>LONGPASS)
            sum+=lenCount;
        if(sum<=LONGPASS)
            fprintf(outputFileP, "%s\n",password);
        free(temp);
        i=0;
        count1=0;
        count2=0;
        count3=0;
        lenCount=0;
    }
    fclose(outputFileP);
    fclose(inputFileP);
}
char* newBuffer(char* buffer , int size){
    char* newBuffer;
    newBuffer=(char*)malloc(size*sizeof(char));
    if (newBuffer==NULL) {
        printf("No memory\n");
        exit(3);
    }
    strcpy(newBuffer, buffer);
    return newBuffer;
}
