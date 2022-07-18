//Assignment 3 
//Campus: Beer-Sheva
//Author: Roni Jack Vituli ID:315369967

#include <stdio.h>
int main(){ // The program receptor the first organ and the difference and how many organs we want.  
	int n; 
	float a1,d,sum,an;
	printf("Please enter the first organ\n");
	scanf("%f",&a1);
	printf("Please enter the difference of series\n");
	scanf("%f",&d);	
	printf("How many Organs you want on your series\n");
	scanf("%d",&n);	
	an=a1+d*(n-1);	
	sum=(n*(a1+an))/2;	
	printf("the %d number is sequence is: %.2f\n",n,an);	
	printf("The sum of all the numbers till the %d number is: %.2f\n",n,sum);
	return 0;	
}		
	
