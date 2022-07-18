//
//  LinkedList.cpp
//  abstract data
//
//  Created by Roni Jack Vituli on 09/11/2020.
//

#include "LinkedList.h"


list* BuildList(){
    list* head = NULL , *temp = head;
    int num;
    printf("Enter numbers to list, -1 to stop: ");
    scanf("%d",&num);
    while(num != -1){
        if(head == NULL){
            head = BuildNode(num);
            temp = head;
        }else{
            temp->next = BuildNode(num);
            temp = temp->next;
        }
        scanf("%d",&num);
    }
    return head;
}



list* BuildNode(int num){
    list* node = (list*)malloc(sizeof(list));
    node->data = num;
    node->next = NULL;
    return node;
}



void PrintList(list* head){
    list* temp = head;
    if(temp == NULL){
        printf("The list is empty\n");
    }else{
        printf("\nThe list is: ");
        while (temp != NULL) {
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int CountNodes(list* head){
    list* temp = head;
    int count = 0;
    if(temp == NULL){
        return count;
    }
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

list* addToSort(list* head,int num){
    list* temp = head, *newNode = BuildNode(num);
    int flag = 0;
    if(head == NULL){
        return newNode;
    }else if(newNode->data <= temp->data and temp->next->data > newNode->data){
        newNode->next = temp;
        return newNode;
    }
    for(; temp != NULL && !flag ; temp = temp->next){
        if(newNode->data >= temp->data and temp->next == NULL){
            temp->next = newNode;
            newNode->next = NULL;
            flag = 1;
        }else if((newNode->data > temp->data) && (newNode->data <= temp->next->data)){
            newNode->next = temp->next;
            temp->next = newNode;
            flag = 1;
        }
    }
    return head;
}

void SelectionSort(list* head)
{
    list* j = (list*)malloc(sizeof(list));
    list* min = (list*)malloc(sizeof(list));
    list* temp = (list*)malloc(sizeof(list));
    for (list* i = head ; i != NULL ; i=i->next)
    {
        min = i;
        for (j = i->next; j != NULL ; j = j->next)
            if ((j->data) < (min->data))
                min = j;
        SWAP(i->data, min->data, temp->data);
        
    }
}

list* newNode(list* head){
    list* newNode = (list*)malloc(sizeof(list));
    int num;
    printf("Enter a number you want to add to the list\n");
    scanf("%d",&num);
    if(head == NULL){
        free(newNode);
        head = BuildNode(num);
        return head;
    }else{
        newNode = BuildNode(num);
        newNode->next = head;
        head = newNode;
    }
    return head;
}

void SearchValue(list* head,int num){
    list* temp = head;
    int index = 0, flag = 0;
    for(; temp != NULL && !flag ; temp = temp->next){
        index++;
        if(temp->data == num)
            flag = 1;
    }
    if(flag)
        printf("Index of value %d is %d\n",num,index);
    else
        printf("Value %d was not found\n",num);
}

void Reverse(list** head){
    list* prev = NULL, *next = NULL;
    list* temp_head = *head;
    
    while(temp_head != NULL){
        next = temp_head->next;
        temp_head->next = prev;
        prev = temp_head;
        temp_head = next;
    }
    *head = prev;
}

int sumList(list* head){
    int sum = 0;
    list* temp = head;
    for(;temp != NULL ; temp = temp->next)
        sum += temp->data;
    return sum;
}


int mul_index_even(list* head){
    int sum = 1, index = 0;
    list* temp = head;
    for (; temp != NULL ; temp = temp->next) {
        index++;
        if(index % 2 == 0)
            sum *= temp->data;
    }
    return sum;
}


list* FreeList(list *head){
    list *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}

list* addToHead(list* head, int num1){ // add node to the the head of the list
    list *new_elem = BuildNode(num1);
    new_elem->next = head;
    return new_elem;
}


list* addToTail(list *head, int num1){
    list *temp, *new_elem;
    new_elem = BuildNode(num1);
    if (head == NULL)
        return new_elem;
    for (temp = head; temp->next != NULL; temp = temp->next);// run to the last node of the list.
    temp->next = new_elem;
    return head;
}



list* addToIndex(list* head, int num1, int index)
{
    list *temp, *new_elem;
    new_elem = BuildNode(num1);
    int i;
    if (head == NULL || index == 1)
    {
        new_elem->next = head;
        return new_elem;
    }
    for (i = 1, temp = head; temp->next != NULL && i < index - 1; temp = temp->next, i++);
    new_elem->next = temp->next;
    temp->next = new_elem;
    return head;
}



list* Delete(list* head, int value){
    list *previous=head, *current=head->next;
    if (head == NULL)
        return head;
    if (head->data == value)
    {
        list *temp = head;
        head = head->next;
        free(temp);
        return head;
    }
    while (previous!=NULL)
    {
        if (previous->data == value)
            break;
        current = previous;
        previous = previous->next;
    }
    if (previous != NULL)
        current->next = previous->next;
    free(previous);
    return head;
}
