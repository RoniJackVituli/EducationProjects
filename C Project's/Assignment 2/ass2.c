//Assignment 2
//Author: Roni Jack Vituli 
//ID:315369967 


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//constants declaration
#define MiniRange 2
#define MaxRange 10
#define NO_ERROR 0
enum {NO,YES};
typedef enum {FALSE,TRUE} BOOL; //new type bool.
// Const variables.
enum {_CheckAndPrint=1, _PrimePalindroms, _RemoveMinDigit, _Game, _PrintPattern, Exit};
//declare functions
void PrintMenu(void);
void ChooseOption(void);
BOOL IsNumberInRange(int,int,int);
int SumDigits(int);
int AbsoluteValue(int);
void PrintNumbers(int);
void CheckAndPrint(void);
void PrimePalindroms(int,int);
BOOL IsPalindrom(int);
BOOL IsPrime(int);
BOOL IsPositive(int);
int IntReverseNumber(int);
long LongReverseNumber(long);
long RemoveMinDigit(long);
int CheckSmallDigit(long);
void Game(void);
void PrintPattern(int,char);
int MaxNum(int,int);
int MiniNum(int,int);

//function Main
int main(){
    ChooseOption();
    return NO_ERROR;
}//end function main

//function's  implementation


void PrintMenu(){//This function no recevie nothing and print the Menu.
    printf("Please choose an option [%d-%d]:\n",_CheckAndPrint, Exit);
    printf("1 - Check Number.\n");
    printf("2 - Prime Palindrome scavenger hunt.\n");
    printf("3 - Remove all min digits.\n");
    printf("4 - The guessing game.\n");
    printf("5 - Print Pattern.\n");
    printf("6 - Exit.\n");
}
//This Function call to func PrintMenu and print the menu and receive form the user input and send it to the function it selected from the menu.
void ChooseOption(){
    int UserChoice,rows;
    int lowRange,highRange;
    char shape;
    long number;
    do {
        PrintMenu();
        scanf("%d",&UserChoice);
        switch (UserChoice) {
            case _CheckAndPrint:
                CheckAndPrint();
                break;
            case _PrimePalindroms:
                printf("Enter the range you want\n");
                scanf("%d%d",&lowRange,&highRange);
                PrimePalindroms(lowRange,highRange);
                printf("\n");
                break;
            case _RemoveMinDigit:
                printf("Enter a number\n");
                scanf("%ld",&number);
                printf("The Mini digit on the number is: %d\n",CheckSmallDigit(number));
                printf("This number is without mini Digit: %ld\n",RemoveMinDigit(number));
                break;
            case _Game:
                Game();
                break;
            case _PrintPattern:
                printf("Enter how many rows you want?\n");
                scanf("%d",&rows);
                printf("Enter some character on the keyboard\n");
                scanf("%s",&shape);
                getchar();
                PrintPattern(rows,shape);
                break;
            case Exit:
                printf("Have a nice day!\n");
                break;
                
            default:
                printf("Worng Choice!\nPlease choose an option from the menu\n");
                break;
        }
        printf("\n");
    } while(UserChoice!=6);
}


//this function check if the number is in the range.
BOOL IsNumberInRange(int lowRange , int highRange, int number){
    int MAX=0,MINI=0;
    MAX = MaxNum(lowRange, highRange);
    MINI = MiniNum(lowRange, highRange);
    return number>=MINI && number<=MAX;
} //end of the fun IsNumberInRange

//This Function recevie int number and calculate the sum of the digits.
int SumDigits(number){
    int lastDigit=0,sum=0;
    while (IsPositive(number)) {
        lastDigit=number%10;
        sum+=lastDigit;
        number=number/10;
    }
    return sum;
}//end func sumDigits


//this function receive int number and return the absloute value
int AbsoluteValue(int negativeNum){
    return negativeNum*(-1);
}//end func abs.



//This Function receive int number and check the range of the three-digits numbers and check if sumDigits equal to the number the function receive.
void PrintNumbers(int number){
    int threeDigit,flag=0;
    for (threeDigit=100; threeDigit<999; threeDigit++) {
        if (SumDigits(threeDigit)==number) {
            printf("%d  ",threeDigit);
            flag=1;
        }
    }
    printf("\n");
    if(flag==1){
        printf("\nThis all three-digit numbers equal to %d\n",number);
    }else{
        printf("There is no three-digit number that is equal to %d\n",number);
    }
}//end function printNumbers.

//This function get Three integer numbers and send them to function IsNumberInRange and check if the user put number in right range and after send to function PrintNumbers and print all three-digits equal to number.
void CheckAndPrint(){
    int low,high,number=0,showError=FALSE;
    do {
        if (showError==TRUE){
            printf("the number %d is not in the range!\nplease choose again.\n\n",number);
        }
        printf("Enter lower limit\n");
        scanf("%d",&low);
        printf("Enter higher limit\n");
        scanf("%d",&high);
        printf("Enter a number between the range you have chosen[%d-%d]\n",low,high);
        scanf("%d",&number);
        showError=TRUE;
    } while (IsNumberInRange(low,high,number)==FALSE);
    PrintNumbers(number);
}//end function checkAndPrint.

//This Function receive two int numbers and print all the Prime and Palindroms numbers in the range the user entered.
void PrimePalindroms(int lowRange,int highRange){
    printf("\n");
    int MAX=0,MINI=0,flag=0;
    MAX=MaxNum(lowRange, highRange);
    MINI=MiniNum(lowRange, highRange);
    for (int number=MINI; number<=MAX; number++){
        if (IsPalindrom(number)==TRUE && IsPrime(number)==TRUE){
            printf("%d  ",number);
            flag=1;
        }
    }
    if (flag==0){
        printf("There is no Prime and Palindroms numbers in this range[%d - %d]\n",lowRange,highRange);
    }else{
        printf("\nThis all Prime and Palindrom numbers in this range[%d - %d]\n",lowRange,highRange);
    }
}//end Function PrimePalindroms.

//This function receive a long number and return value int that he the mini digit on the number.
int CheckSmallDigit(long number){
    int lastDigit=0;
    int mini=0;
    mini=number%10;
    while (number>0){
        lastDigit=number%10;
        if (mini>lastDigit)
            mini=lastDigit;
        number=number/10;
    }
    return mini;
}//end function checkSmallDigit.

//This function receive a long number and remove the mini digit form the number and return the new number without mini digit.
long RemoveMinDigit(long number){
    long mini=0;
    long newNum=0;
    if (number<0)
        number=number*(-1);
    mini=CheckSmallDigit(number);
    while (number>0) {
        newNum=newNum*10;
        if(number%10!=mini)
            newNum=newNum+(number%10);
        else
            newNum=newNum/10;
        
        number=number/10;
    }
    return LongReverseNumber(newNum);
}//end function RemoveMinDigit.

//This function receive a integer number and return the reverse the number.
int IntReverseNumber(int number){
    int newNumber=0;
    while (number!=0) {
        newNumber=newNumber*10;
        newNumber=newNumber+(number%10);
        number=number/10;
    }
    return newNumber;
}//end function reversNumber

//This function receive a long number and return the reverse number.
long LongReverseNumber(long number){
    long newNumber=0;
    while (number!=0){
        newNumber=newNumber*10;
        newNumber=newNumber+(number%10);
        number=number/10;
    }
    return newNumber;
}
//This function receive a integer number and check if number is Prime and return TRUE OR FALSE.
BOOL IsPrime(int number){
    int counter=0;
    for (int i=1; i<=number; i++){
        if(number%i==0)
            counter++;
    }
    return counter==2;
}//end function isPrime.

//This function receive a integer number and check if the number is Palindrom and return TRUE OR FALSE.
BOOL IsPalindrom(int number){
    int checkNumber;
    checkNumber=IntReverseNumber(number);
    return checkNumber==number;
}//end function isPalindrom.

//This function receive a integer number and check if number is bigger than zero and return TRUE OR FALSE.
BOOL IsPositive(int number){
    return number>0;
    
}//end function isPositive.

//This function is Memory Game.
//in this function the user play a game. the user puts range and the program send a random number between the range
//and the user need to choice few guesses between 2-10 and guess the right number to come out in random number.
void Game(){
    srand(time(NULL)); // Initialization of random
    int randomNumber,flag;
    int num1,num2,checkGuess,AmountGuess;
    int MAX=0,MINI=0;
    int userChoice;
    printf("Do want to start the game? Yes - %d / NO - %d\n",YES,NO);
    scanf("%d",&userChoice);
    if(userChoice == YES){
        do{
            flag=0;
            printf("Enter a number\n");
            scanf("%d",&num1);
            printf("Enter a second number\n");
            scanf("%d",&num2);
            MAX=MaxNum(num1,num2); // bring back maximum number
            MINI=MiniNum(num1,num2); // bring back the minimum number
            randomNumber = (rand() % (MAX - MINI + 1)) + MINI;//Random Number.
            printf("Enter the number of guesses you would like to make [%d-%d]:\n",MiniRange,MaxRange);
            scanf("%d",&AmountGuess);
            while (AmountGuess<MiniRange || AmountGuess>MaxRange) {
                printf("The number entered is out of the range.\nPlease enter again guesses you would like to make[%d-%d]\n",MiniRange,MaxRange);
                scanf("%d",&AmountGuess);
            }
            if(IsNumberInRange(MiniRange, MaxRange, AmountGuess)){ // check if the guess is in the range.5
                printf("Enter your guess (you have %d guesses left)\n",AmountGuess);
                while (IsPositive(AmountGuess) && flag==0){
                    scanf("%d",&checkGuess);
                    AmountGuess--;
                    if (checkGuess==randomNumber){
                        printf("Congratulations – you have won!\n");
                        flag=1;
                    }else if(AmountGuess==0){
                        printf("YOU ARE LOSE :(\n");
                        printf("The computer number is: %d\n",randomNumber);
                        if (checkGuess==randomNumber-1 || checkGuess==randomNumber+1)
                            printf("You was so close!!!!!!\n");
                    }else if(checkGuess>randomNumber && IsNumberInRange(MINI,MAX,checkGuess) && IsPositive(AmountGuess)){
                        printf("Enter a lower number (you have %d guesses left)\n",AmountGuess);
                    }else if(checkGuess<randomNumber && IsNumberInRange(MINI,MAX,checkGuess) && IsPositive(AmountGuess)){
                        printf("Enter a higher number (you have %d guesses left)\n",AmountGuess);
                    }else if(IsNumberInRange(MINI,MAX,checkGuess)==FALSE && IsPositive(AmountGuess)){
                        printf("Invalid guess – not in the required range [%d-%d]\n",MINI,MAX);
                        printf("Enter your guess IN RANGE YOU CHOICE (you have %d guesses left)\n",AmountGuess);
                    }
                }
                printf("\n");
    
            }else{
                    printf("The number you entered %d is not in a range between [%d-%d]\n\n",AmountGuess,MiniRange,MaxRange);
             }
            printf("Do want to start the game agian? Yes - %d / NO - %d\n",YES,NO);
            scanf("%d",&userChoice);
        }while(userChoice==YES);
        printf("\nThank you and goodbye :)\n");
    }else{
      printf("\nThank you and goodbye :)\n");
    }
}//End Function Game.

//This function receive a integer lines and char and print Hourglass
void PrintPattern(int lines,char shape){
    if (IsPositive(lines)==FALSE){//it check if the user put negative number and change it to positive.
        lines=AbsoluteValue(lines);
    }		
    for (int rowRight=0,rowLeft=(lines*2)-1; rowRight<lines*2; rowRight++,rowLeft--) {
        for (int columnUP=0 ,columnDOWN=(lines*2)-1 ; columnUP<lines*2 ; columnUP++,columnDOWN--) {
            if(columnUP>=rowRight && rowLeft>columnUP && rowLeft>=columnDOWN && columnDOWN>rowRight) {
                printf("%c",shape);
            }else if(rowRight>=columnDOWN && columnUP>=rowLeft && columnDOWN>rowLeft && rowRight>columnUP){
                printf("%c",shape);
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
}//end Function PrintPattern.

//This function receive two integer numbers and return the max number.
int MaxNum(int num1,int num2){
    if (num1>num2)
        return num1;
    else
        return num2;
    
}//end function MaxNum.

//This function receive two integer numbers and return the mini number.
int MiniNum(int num1,int num2){
    if (num1>num2)
        return num2;
    else
        return num1;

}//end function MiniNum.



//end Assignment 2.
