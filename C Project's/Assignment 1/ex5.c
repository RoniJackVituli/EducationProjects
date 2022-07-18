// Assignment 5 	
// Campus: Beer-Sheva
// Author: Roni Jack Vituli


#include <stdio.h>
int main(){//The Program receptor birthday dates and check how is younger. 
	int dayA, monthA, yearA,dateA;	
	int dayB, monthB, yearB,dateB;
	printf("Enter the birthday date\n");
	scanf("%d%d%d",&dayA,&monthA,&yearA);
    dateA=((yearA*10000)+(monthA*100))+dayA;
	printf("Enter the second birthday date\n");
	scanf("%d%d%d",&dayB,&monthB,&yearB);	
	dateB=((yearB*10000)+(monthB*100))+dayB;	
	if(dateA>dateB){
		printf("Thr first date is younger\n");
	}else{
		printf("The second date is younger\n");
	}
	return 0;
}
