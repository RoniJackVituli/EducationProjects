//
//  LinkedList.hpp
//  abstract data
//
//  Created by Roni Jack Vituli on 09/11/2020.
//

#ifndef LinkedList_h
#define LinkedList_h



#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t)((t)=(x),(x)=(y),(y)=(t))
#define NO_ERROR 0

typedef struct List list;
struct List{
    int data;
    list* next;
};




list* BuildList();
list* BuildNode(int);
list* newNode(list*);
list* FreeList(list *head);
list* addToHead(list* head, int num1);
list* addToTail(list* head, int num1);
list* addToIndex(list* head, int num1, int index);
list* addToSort(list* head,int num);
list* Delete(list* head, int value);


void SelectionSort(list* head);
void Reverse(list** head);
void SearchValue(list*,int);
void PrintList(list*);
int CountNodes(list*);
int sumList(list* head);
int mul_index_even(list* head);

#endif /* LinkedList_h */
