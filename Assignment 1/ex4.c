//Assignment 4 
//Campus: Beer-Sheva
//Author: Roni Jack Vituli ID:315369967


// The program receptor an integer number and check if number is postive or negative and even or odd. 
#include <stdio.h>
int main(){
	int number;
	printf("Enter what number you want.\n");
	scanf("%d",&number);
	if(number>0){
		if(number%2==0){
			printf("The number %d is positive and even\n",number);
		}else{
			printf("The number %d is positive and odd\n",number);
		}
	}else if(number==0){
		printf("The number %d is zero and even\n",number);
	}else if(number<0){
		if(number%2==0){
			printf("The number %d is negative and even\n",number);
		}else{	 
			printf("The number %d is negative and odd\n",number);	
		}
	}

	return 0;	
}
