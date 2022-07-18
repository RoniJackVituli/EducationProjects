//  main.cpp
//
//  Created by Roni Jack Vituli ID: 315369967.

#include "LinkedList.h"

int main(){
    list* head = NULL;
    int num, index;
    head = BuildList();
    PrintList(head);
    printf("The lenth is: %d\n\n",CountNodes(head));

    printf("Enter a number for new head node: ");
    scanf("%d",&num);
    head = addToHead(head, num);

    PrintList(head);
    printf("The lenth is: %d\n\n",CountNodes(head));

    printf("Enter a number for new Tail node: ");
    scanf("%d",&num);
    head = addToTail(head , num);

    PrintList(head);
    printf("The lenth is: %d\n\n",CountNodes(head));


    printf("Enter a number and an index for new node: ");
    scanf("%d%d",&num,&index);
    head = addToIndex(head, num, index);
    PrintList(head);

    printf("Enter a value for find: ");
    scanf("%d",&num);
    SearchValue(head, num);
    
    printf("Enter a value for find: ");
    scanf("%d",&num);
    SearchValue(head, num);

    printf("\n\nSorted list: ");
    SelectionSort(head);
    PrintList(head);
    
    printf("\n\nEnter a number for new node sort list: ");
    scanf("%d",&num);
    head = addToSort(head, num);
    PrintList(head);
    printf("The lenth is: %d\n\n",CountNodes(head));
    
    printf("Reverse List\n");
    Reverse(&head);
    PrintList(head);
    
    printf("\nEnter a value for delete: ");
    scanf("%d",&num);
    head = Delete(head, num);
    PrintList(head);
    printf("The lenth is: %d\n\n",CountNodes(head));
    
    printf("Sum of list is: %d\n\n",sumList(head));
    printf("Product of even index values of list is: %d\n",mul_index_even(head));
    
    head = FreeList(head);
    return NO_ERROR;
}
