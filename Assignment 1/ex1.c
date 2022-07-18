//Assignment 1
//Campus:Beer Sheva
//Author: Roni Jack Vituli ID:315369967.

#include <stdio.h>
int main(){
	 //The Program receptor a real number and converts the number to several options.	
	float num1;
	printf("Enter a number\n");
	scanf("%f",&num1); 
	printf("Your value is: %.2f\n",num1);
	printf("The integer value is: %d\n", (int)num1);	
	printf("The integer hxdecimal is: 0x%X\n",(int)num1);	
	printf("The char is: %c\n", (char)((int)num1));	

	return 0;
}
