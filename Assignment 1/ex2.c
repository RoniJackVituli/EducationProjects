

//Assignment 2
//Campus: Beer-Sheva
//Author: Roni Jack Vituli ID:315369967

#include <stdio.h>
int main(){
	// The program receptor grades of the coures and calculate the average of the coures.
	// for example gradeA is 80 and the weight of garadeA is 20 present so from grade A you have 16 points.

	int gradeA, gradeB, gradeC; 	
	float weightA,weightB,weightC; 	
	float avg;	
	printf("Enter your grades\n");
	scanf("%d%d%d",&gradeA,&gradeB,&gradeC); 	
	printf("Enter your wegiht of the percent test\n");
	printf("example: Grade A is 80\nthe wegiht of grade A is: 20 precent.\nso from garde A you have 16 points\n");
	scanf("%f%f%f",&weightA,&weightB,&weightC);	
	avg=((gradeA*weightA)+(gradeB*weightB)+(gradeC*weightC))/100;	
	printf("Your Final Garde is:  %.2f\n",avg);
	return 0;	
}		 
	
